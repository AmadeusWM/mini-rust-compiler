#pragma once
#include "ast_node.h"
#include "spdlog/spdlog.h"
#include "util.h"
#include "visitor.h"
#include <string>
#include <variant>

namespace AST {
class PrintVisitor : public AST::Visitor {
  private:
  int indent = 0;
  void print(std::string str)
  {
    std::string ind = "";
    for (int i = 0; i < indent; i++) {
      ind += "  ";
    }
    spdlog::debug("{}|-{}", ind, str);
  }
  void wrap(std::function<void()> func)
  {
    indent += 1;
    func();
    indent -= 1;
  }

  public:
  void visit(const Crate& crate) override
  {
    print("Crate");
    for (const auto& child : crate.items) {
      wrap([this, &child]() { visit(*child); });
    }
  };

  void visit(const Item& item) override
  {
    std::visit(
        overloaded { [this](const P<FnDef>& fn) {
          print("FnDef: " + fn->ident.identifier);
          wrap([this, &fn]() { visit(*(fn.get()->body)); });
        } },
        item.kind);
  }

  void visit(const Block& node) override
  {
    print("Block");
    for (const auto& child : node.statements) {
      wrap([this, &child]() { visit(*child); });
    }
  }

  void visit(const Expr& expr) override
  {
    std::visit(
        overloaded {
            [this](const Lit& lit) {
              std::visit(
                  overloaded {
                      [this](const int i) { print("Lit Int: " + std::to_string(i)); },
                      [this](const std::string& s) { print("Lit String: " + s); } },
                  lit.kind);
            },
            [this](const P<Block>& block) {
              wrap([this, &block]() { visit(*block); });
            },
            [this](const Path& path) {
              wrap([this, &path]() { visit(path); });
            },
        },
        expr.kind);
  }

  void visit(const Stmt& stmt) override
  {
    std::visit(
      overloaded {
        [this](const P<Let>& let) {
          std::visit(overloaded {
              [this](const Ident& path) { } },
            let->pat);
          visit(*let);
        },
        [this](const P<Expr>& expr) {
          wrap([this, &expr]() {
            Visitor::visit(*expr);
          });
        },
        [this](const P<Item>& item) {
          visit(*item);
        },
      },
      stmt.kind);
  }

  void visit(const Let& let) override
  {
    wrap([this, &let]() {
      std::visit(
          overloaded {
              [this](const Decl& decl) { print("Decl"); },
              [this](const P<Expr>& expr) {
                print("Expr");
                wrap([this, &expr]() {
                  visit(*expr);
                });
              } },
          let.kind);
    });
  }

  void visit(const Path& path) override
  {
    std::string path_str = "Path: ";
    for (const auto& seg : path.segments) {
      path_str = path_str + seg.ident.identifier;
    }
    print(path_str);
  }
};
} // namespace AST
