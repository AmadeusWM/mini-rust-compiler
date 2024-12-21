#pragma once

#include "nodes/body.h"
#include "nodes/expr.h"
#include "nodes/stmt.h"
#include "nodes/type.h"
#include "visitors/visitor.h"
#include <memory>

namespace AST{
class LowerAstVisitor : public Visitor {
  TAST::Crate crate;

  void visit(const Crate& crate) override {
    for (const auto& item : crate.items) {
      visit(*item);
    }
  }

  void visit(const Item& item) {
    std::visit(
      overloaded {
        [&](const P<FnDef>& fn) {
          this->crate.bodies.insert({
            item.id,
            TAST::Body {
              .expr = P<TAST::Expr>(new TAST::Expr {
                .id = fn->id,
                .kind = TAST::ExprKind {this->resolve_body(*fn->body)},
                .ty = TAST::InferTy{}
              })
            }
          });
        }
      }, item.kind);
  }

  P<TAST::Block> resolve_body(const Block& block) {
    std::vector<P<Stmt>> statements{};
    for (const auto& stmt : block.statements) {
      statements.push_back(this->resolve_statement(*stmt));
    }

    return std::make_unique<TAST::Block>(TAST::Block {

    });
  }

  P<TAST::Stmt> resolve_statement(const Stmt& stmt) {
    return TAST::Stmt{

    };
  }
};
}
