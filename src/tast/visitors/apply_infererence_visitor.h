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
      [this](Lit& lit) { visit(lit); },
      [this](AST::Ident& ident ) {},
      [this](P<Binary>& binary) { visit(*binary->lhs); visit(*binary->rhs); },
      [this](P<Call>& call) {MutWalkVisitor::visit(*call); },
    }, expr.kind);
  }

  void visit(Lit& lit) override {
    lit.ty = ctx.getType(lit.id);
  }
};
}
