#pragma once

#include "nodes/type.h"
#include "visitors/tast_visitor.h"
namespace TAST {


class TypecheckVisitor : public MutWalkVisitor {
  class TypecheckException : public std::runtime_error {
  public:
      TypecheckException(const std::string& message)
          : std::runtime_error("(Type Check Error) " + message) {}
  };


  public:
  void visit(Crate& crate) override {
    for (const auto& [key, body] : crate.bodies) {
      visit(*body);
    }
  }
  void visit(Body& body) override {
   visit(*body.expr);
  }
  void visit(Block& block) override {
    for (const auto& stmt : block.statements) {
      visit(*stmt);
    }
  }

  void visit(Stmt& stmt) override {
    std::visit(overloaded {
      [this](const P<Let>& let) { visit(*let); },
      [this](const P<Expr>& expr) { visit(*expr); },
      [this](const P<Semi>& semi) { visit(*semi->expr); }
    }, stmt.kind);
  }
  void visit(Let& let) override {
    if (let.initializer.has_value()) {
      visit(*let.initializer.value());
    }
  }
  void visit(AST::Path& path) override {
    for (auto& segment : path.segments) {
      visit(segment);
    }
  }
  void visit(AST::PathSegment& segment) override {
  }
  void visit(Expr& expr) override {
    std::visit(overloaded {
      [&](P<Block>& block) { visit(*block); },
      [&](Lit& lit) { expr.ty = resolve_lit(lit); },
      [&](P<Binary>& binary) { expr.ty = resolve_binary(*binary); },
      [&](AST::Path& path) { visit(path); },
      [&](P<Call>& call) { visit(*call); },
    }, expr.kind);

  }

  Ty resolve_binary(Binary& bin) {
    visit(*bin.lhs);
    visit(*bin.rhs);

    Opt<Ty> ty = bin.lhs->ty.resolve(bin.rhs->ty);
    if (ty.has_value()) {
      return ty.value();
    }
    else {
      throw TypecheckException(fmt::format("Binary operation between different types at nodes: {} and {}", bin.lhs->id, bin.rhs->id));
    }
  }

  Ty resolve_lit(Lit& lit) {
    return std::visit(overloaded {
      [&](int i) { return Ty(InferTy(IntVar{})); },
      [&](std::string s) { return Ty(StrTy{}); }
    }, lit.kind);
  }

  void visit(Call& call) override {

  }
};
}
