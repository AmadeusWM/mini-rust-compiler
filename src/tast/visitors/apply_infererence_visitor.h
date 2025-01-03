#pragma once

#include "infer_ctx.h"
#include "visitors/tast_visitor.h"
namespace TAST {
class ApplyInferenceVisitor: public MutWalkVisitor {
  private:
  const InferCtx& ctx;
  public:
  ApplyInferenceVisitor(const InferCtx& ctx): ctx(ctx) {}

  void visit(Body& body) override {
   visit(*body.expr);
  }

  void visit(Let& let) override {
    let.ty = ctx.getType(let.id);
    MutWalkVisitor::visit(let);
  }
  void visit(Expr& expr) override {
    expr.ty = ctx.getType(expr.id);
    std::visit(overloaded {
      [this](P<Block>& block) { MutWalkVisitor::visit(*block); },
      [this](P<Ret>& ret) { MutWalkVisitor::visit(*ret); },
      [this](P<Loop>& loop) { MutWalkVisitor::visit(*loop); },
      [this](P<If>& ifExpr) { MutWalkVisitor::visit(*ifExpr); },
      [this](Lit& lit) { visit(lit); },
      [this](Break& br) {},
      [this](AST::Ident& ident ) {},
      [this](P<Binary>& binary) { visit(*binary->lhs); visit(*binary->rhs); },
      [this](P<Call>& call) { visit(*call); },
    }, expr.kind);
  }

  void visit(Lit& lit) override {
    lit.ty = ctx.getType(lit.id);
  }

  void visit(Call& call) override {
    for(auto& arg: call.params) {
      visit(*arg);
    }
  }
};
}
