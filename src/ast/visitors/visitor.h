#pragma once
#include "../ast_node.h"
#include "nodes/expr.h"

namespace AST {
  class Visitor {
    public:
    virtual void visit(const Crate& crate)
    {
      for (const auto& child : crate.items) {
        visit(*child);
      }
    };

    virtual void visit(const Item& item)
    {
      std::visit(
          overloaded { [this](const P<FnDef>& fn) { visit(*fn); } }, item.kind);
    }

    virtual void visit(const FnDef& node) { visit(*node.body); }

    virtual void visit(const FnSig& sig) {
      for (const auto& param : sig.inputs) {
        visit(*param);
      }
    }

    virtual void visit(const Param& param) {
    }

    virtual void visit(const Block& node)
    {
      for (const auto& child : node.statements) {
        visit(*child);
      }
    }

    virtual void visit(const Stmt& node)
    {
      std::visit(
          overloaded {
              [this](const P<Expr>& expr) { visit(*expr); },
              [this](const P<Let>& let) { visit(*let); },
              [this](const P<Item>& item) { visit(*item); },
              [this](const P<Semi>& semi) { visit(*semi->expr); }
          }, node.kind);
    }

    virtual void visit(const Ret& ret) {
      visit(*ret.expr);
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
          [this](const Break& lit) { },
          [this](const P<Ret>& ret) { visit(*ret); },
          [this](const P<If>& ifExpr) { visit(*ifExpr); },
          [this](const P<While>& whileExpr) { visit(*whileExpr); },
          [this](const P<Loop>& loopExpr) { visit(*loopExpr); },
          [this](const P<Block>& block) { visit(*block); },
          [this](const P<Assign>& assign) { visit(*assign); },
          [this](const Path& path) { },
          [this](const P<Binary>& binary) { visit(*binary); },
          [this](const P<Unary>& unary) {visit(*unary);},
          [this](const P<Call>& call) { visit(*call); }
      }, expr.kind);
    }

    virtual void visit(const Unary& unary) {
      visit(*unary.expr);
    }

    virtual void visit(const Binary& binary) {
      visit(*binary.lhs);
      visit(*binary.rhs);
    }

    virtual void visit(const Assign& assign) {
      visit(*assign.rhs);
    }

    virtual void visit(const Loop& loopExpr) {
      visit(*loopExpr.block);
    }

    virtual void visit(const Call& call) {
      for (const auto& param : call.params) {
        visit(*param);
      }
    }

    virtual void visit(const Lit& lit) {
      std::visit(
        overloaded {
            [this](const int i) {},
            [this](const std::string& s) {}
        }, lit.kind);
    }

    virtual void visit(const If& ifExpr) {
      visit(*ifExpr.cond);
      visit(*ifExpr.then_block);
      if (ifExpr.else_block.has_value()){
        visit(*ifExpr.else_block.value());
      }
    }

    virtual void visit(const While& whileExpr) {
      visit(*whileExpr.cond);
      visit(*whileExpr.block);
    }
  };
}
