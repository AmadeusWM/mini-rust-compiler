#pragma once

#include "nodes/type.h"
#include "visitors/tast_visitor.h"
namespace TAST {
class TypecheckException : public std::runtime_error {
public:
    TypecheckException(const std::string& message)
        : std::runtime_error("(Type Check Error) " + message) {}
};

class TypecheckVisitor : public MutWalkVisitor {
  private:
  Crate& crate;

  public:
  TypecheckVisitor(Crate& crate) : crate{crate}{}

  void typecheck() {
    this->visit(crate);
  }
    
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

  void visit(Expr& expr) override {
    std::visit(overloaded {
      [&](P<Block>& block) { visit(*block); },
      [&](Lit& lit) { expr.ty = resolve_lit(lit); },
      [&](AST::Ident& ident) {
        // TODO: resolve idetifier
        throw std::runtime_error("cannot resolve identifier type yet, TODO: we need to keep track of the bindings per scope and then lookup the types in this table");
      },
      [&](P<Binary>& binary) { expr.ty = resolve_binary(*binary); },
      [&](P<Call>& call) { resolve_call(*call); },
    }, expr.kind);

  }

  Ty resolve_call(Call& call) {
    // this->crate.bodies;
    return {};
  }

  Ty resolve_binary(Binary& bin) {
    visit(*bin.lhs);
    visit(*bin.rhs);

    Opt<Ty> ty = bin.lhs->ty.resolve(bin.rhs->ty);
    if (ty.has_value()) {
      return ty.value();
    }
    else {
      throw TypecheckException(fmt::format("Binary operation between incompattible types '{}' and '{}' at nodes: {} and {}", bin.lhs->ty.to_string(), bin.rhs->ty.to_string(), bin.lhs->id, bin.rhs->id));
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
