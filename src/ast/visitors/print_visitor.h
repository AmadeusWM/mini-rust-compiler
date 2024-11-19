#pragma once
#include "spdlog/spdlog.h"
#include "visitor.h"
#include <string>

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
      wrap([this, &child]() { visit(child); });
    }
  };

  void visit(const Item& item) override
  {
    std::visit(
        overloaded { [this](const P<FnDef>& fn) {
          print("FnDef");
          wrap([this, &fn]() { visit(*(fn.get()->body)); });
        } },
        item.kind);
  }

  void visit(const Block& node) override
  {
    print("Block");
    for (const auto& child : node.statements) {
      wrap([this, &child]() { visit(child); });
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
            } },
        expr.kind);
  }

  void visit(const Stmt& stmt) override
  {
    std::visit(
        overloaded {
            [this](const P<Let>& let) {
              std::visit(
                  overloaded {
                      [this](const Decl& decl) { print("Let Decl"); },
                      [this](const P<Expr>& expr) {
                        print("Let Expr");
                        wrap([this, &expr]() {
                          visit(*expr);
                        });
                      } },
                  let->kind);
            },
            [this](const P<Expr>& expr) {
              Visitor::visit(*expr);
            } },
        stmt.kind);
  }
};
} // namespace AST
