#pragma once

#include "../tast_node.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include <spdlog/spdlog.h>
#include <variant>

namespace TAST {
template <class T> class Visitor {
  public:
  virtual T visit(const Crate& crate) = 0;
  virtual T visit(const Body& body) = 0;
  virtual T visit(const Block& block) = 0;
  virtual T visit(const If& ifExpr) = 0;
  virtual T visit(const Loop& loopExpr) = 0;
  virtual T visit(const Stmt& stmt) = 0;
  virtual T visit(const Let& let) = 0;
  virtual T visit(const Expr& expr) = 0;
  virtual T visit(const Lit& lit) = 0;
  virtual T visit(const Call& call) = 0;
  virtual T visit(const Ret& ret) = 0;
};

/**
* allows a visitor to change nodes
*/
template <class T> class MutVisitor {
  public:
  virtual T visit(Crate& crate) = 0;
  virtual T visit(Body& body) = 0;
  virtual T visit(Block& block) = 0;
  virtual T visit(If& ifExpr) = 0;
  virtual T visit(Loop& loopExpr) = 0;
  virtual T visit(Stmt& stmt) = 0;
  virtual T visit(Let& let) = 0;
  virtual T visit(Expr& expr) = 0;
  virtual T visit(Lit& lit) = 0;
  virtual T visit(Call& call) = 0;
  virtual T visit(Ret& ret) = 0;
};

class WalkVisitor : public Visitor<void> {
  public:
  void visit(const Crate& crate) override {
    for (const auto& [key, body] : crate.bodies) {
      visit(*body);
    }
  }
  void visit(const Body& body) override {
   visit(*body.expr) ;
  }
  void visit(const Block& block) override {
    for (const auto& stmt : block.statements) {
      visit(*stmt);
    }
    if (block.expr.has_value()) {
      visit(*block.expr.value());
    }
  }
  void visit(const Stmt& stmt) override {
    std::visit(overloaded {
      [this](const P<Let>& let) { visit(*let); },
      [this](const P<Expr>& expr) { visit(*expr); },
      [this](const P<Semi>& semi) { visit(*semi->expr); }
    }, stmt.kind);
  }
  void visit(const Let& let) override {
    if (let.initializer.has_value()){
      visit(*let.initializer.value());
    }
  }
  void visit(const Expr& expr) override {
    std::visit(overloaded {
      [this](const P<Block>& block) { visit(*block); },
      [this](const P<If>& ifExpr) { visit(*ifExpr); },
      [this](const P<Loop>& loopExpr) { visit(*loopExpr); },
      [this](const P<Ret>& ret) { visit(*ret); },
      [this](const Lit& lit) { visit(lit); },
      [this](const Break& breakExpr) { },
      [this](const AST::Ident& ident) { },
      [this](const P<Binary>& binary) { visit(*binary->lhs); visit(*binary->rhs); },
      [this](const P<Call>& call) { visit(*call); },
    }, expr.kind);
  }

  void visit(const If& ifExpr) override {
    visit(*ifExpr.cond);
    visit(*ifExpr.then_block);
    if (ifExpr.else_block.has_value()) {
      visit(*ifExpr.else_block.value());
    }
  }

  void visit(const Loop& loopExpr) override {
    visit(*loopExpr.block);
  }

  void visit(const Ret& ret) override {
    visit(*ret.expr);
  }

  void visit(const Call& call) override {

  }

  void visit(const Lit& lit) override {

  }
};

class MutWalkVisitor : public MutVisitor<void> {
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
  void visit(Expr& expr) override {
    std::visit(overloaded {
      [this](P<Block>& block) { visit(*block); },
      [this](Break& breakExpr) { },
      [this](P<If>& ifExpr) { visit(*ifExpr); },
      [this](P<Loop>& loopExpr) { visit(*loopExpr); },
      [this](P<Ret>& ret) { visit(*ret); },
      [this](Lit& lit) { visit(lit); },
      [this](AST::Ident& ident ) {},
      [this](P<Binary>& binary) { visit(*binary->lhs); visit(*binary->rhs); },
      [this](P<Call>& call) { visit(*call); },
    }, expr.kind);
  }

  void visit(If& ifExpr) override {
    visit(*ifExpr.cond);
    visit(*ifExpr.then_block);
    if (ifExpr.else_block.has_value()) {
      visit(*ifExpr.else_block.value());
    }
  }

  void visit(Loop& loopExpr) override {
    visit(*loopExpr.block);
  }

  void visit(Ret& ret) override {
    visit(*ret.expr);
  }

  void visit(Lit& lit) override {

  }

  void visit(Call& call) override {

  }
};
}
