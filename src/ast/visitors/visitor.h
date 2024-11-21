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
              [this](const P<Expr>& expr) { visit(*expr); },
              [this](const P<Let>& let) { visit(*let); },
              [this](const P<Item>& item) { visit(*item); }
          }, node.kind);
    }

    virtual void visit(const Let& let) {
      std::visit(
          overloaded {
              [this](const Decl& decl) {},
              [this](const P<Expr>& expr) { visit(*expr); }
      }, let.kind);
    }

    virtual void visit(const Path& path) {
      for (const auto& segment : path.segments) {
        visit(segment);
      }
    }

    virtual void visit(const PathSegment& segment) {
    }

    virtual void visit(const Expr& expr)
    {
      std::visit(
        overloaded {
          [this](const Lit& lit) { visit(lit); },
          [this](const P<Block>& block) { visit(*block); },
          [this](const Path& path) { }
      }, expr.kind);
    }

    virtual void visit(const Lit& lit) {
      std::visit(
        overloaded {
            [this](const int i) {},
            [this](const std::string& s) {}
        }, lit.kind);
    }
  };
}
