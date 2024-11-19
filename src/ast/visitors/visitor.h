#pragma once
#include "../node.h"

namespace AST {
  class Visitor {
    public:
    virtual void visit(const Crate& crate)
    {
      for (const auto& child : crate.items) {
        visit(child);
      }
    };

    virtual void visit(const Item& item)
    {
      std::visit(
          overloaded { [this](const P<FnDef>& fn) { visit(*fn); } }, item.kind);
    }

    virtual void visit(const FnDef& node) { visit(*node.body); }

    virtual void visit(const Block& node)
    {
      for (const auto& child : node.statements) {
        visit(child);
      }
    }

    virtual void visit(const Stmt& node)
    {
      std::visit(
          overloaded {
              [this](const P<Let>& let) {
                std::visit(
                    overloaded {
                        [this](const Decl& decl) {},
                        [this](const P<Expr>& expr) { visit(*expr); } },
                    let->kind);
              },
              [this](const P<Expr>& expr) { visit(*expr); } },
          node.kind);
    }

    virtual void visit(const Expr& expr)
    {
      std::visit(
          overloaded {
              [this](const Lit& lit) {
                std::visit(
                    overloaded {
                        [this](const int i) {}, [this](const std::string& s) {} },
                    lit.kind);
              },
              [this](const P<Block>& block) { visit(*block); } },
          expr.kind);
    }
  };
}
