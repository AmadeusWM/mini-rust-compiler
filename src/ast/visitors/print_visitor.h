#pragma once
#include "ast_node.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "spdlog/spdlog.h"
#include "util.h"
#include "visitor.h"
#include <fmt/core.h>
#include <string>
#include <variant>

namespace AST {
class PrintVisitor : public AST::Visitor {
  private:
  int indent = 0;
  void print(std::string str, Opt<NodeId> id = std::nullopt)
  {
    std::string ind = "";
    for (int i = 0; i < indent; i++) {
      ind += "  ";
    }
    if (id.has_value()) {
      spdlog::debug("{}|-{} ({})", ind, str, id.value());
    }
    else {
      spdlog::debug("{}|-{}", ind, str);
    }
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
    print("Crate", crate.id);
    wrap([&] {
      for (const auto& child : crate.items) {
        visit(*child);
      }
    });
  };

  void visit(const Item& item) override
  {
    print("Item", item.id);
    wrap([&] {
      std::visit(
          overloaded { [this](const P<FnDef>& fn) {
            print("FnDef: " + fn->ident.identifier, fn->id);
            wrap([this, &fn]() { visit(*(fn.get()->body)); });
          }
      }, item.kind);
    });
  }

  void visit(const Block& node) override
  {
    print("Block", node.id);
    wrap([&]() {
      for (const auto& child : node.statements) {
        visit(*child);
      }
    });
  }

  void visit(const Expr& expr) override
  {
    print("Expr", expr.id);
    wrap([&]() {
      std::visit(overloaded {
        [this](const P<Ret>& ret) {
          visit(*ret->expr);
        },
        [this](const Lit& lit) {
          std::visit(
            overloaded {
                [&](const int i) { print("Lit Int: " + std::to_string(i), lit.id); },
                [&](const std::string& s) { print("Lit String: " + s, lit.id); }
            }, lit.kind);
        },
        [this](const P<Block>& block) {
          visit(*block);
        },
        [this](const Path& path) {
          visit(path);
        },
        [this](const P<Binary>& binary) {
          visit(*binary->lhs);
          print(fmt::format("BinOp: {}",
            std::visit(overloaded {
              [](const Bin::Add) { return "Add"; },
              [](const Bin::Sub) { return "Sub"; }
            }, binary->op))
          );
          visit(*binary->rhs);
        },
        [this](const P<Call>& call) {
          print("Call", call->id);
          wrap([this, &call]() {
            visit(call->path);
            for (const auto& param : call->params) {
              visit(*param);
            }
          });
        }
      }, expr.kind);
    });
  }

  void visit(const Stmt& stmt) override
  {
    print("Stmt", stmt.id);
    wrap([&]() {
      Visitor::visit(stmt);
    });
  }

  void visit(const Let& let) override
  {
    print("Let", let.id);
    wrap([this, &let]() {
      visit(*let.pat);
      std::visit(
          overloaded {
              [this](const Decl& decl) { print("Decl"); },
              [this](const P<Expr>& expr) {
                visit(*expr);
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

  void visit(const Pat& pat) {
    std::visit(overloaded {
      [&](const Ident& ident) {
        print(fmt::format("Ident: {}", ident.identifier));
      }
    }, pat.kind);
  }
};
} // namespace AST
