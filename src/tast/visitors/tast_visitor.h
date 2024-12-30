#pragma once

#include "../tast_node.h"
#include <spdlog/spdlog.h>
#include <variant>

namespace TAST {
template <class T> class Visitor {
  public:
  virtual T visit(const Crate& crate) = 0;
  virtual T visit(const Body& body) = 0;
  virtual T visit(const Block& block) = 0;
  virtual T visit(const Stmt& stmt) = 0;
  virtual T visit(const Let& let) = 0;
  virtual T visit(const AST::Path& path) = 0;
  virtual T visit(const AST::PathSegment& segment) = 0;
  virtual T visit(const Expr& expr) = 0;
  virtual T visit(const Lit& lit) = 0;
  virtual T visit(const Call& call) = 0;
};

/**
* allows a visitor to change nodes
*/
template <class T> class MutVisitor {
  public:
  virtual T visit(Crate& crate) = 0;
  virtual T visit(Body& body) = 0;
  virtual T visit(Block& block) = 0;
  virtual T visit(Stmt& stmt) = 0;
  virtual T visit(Let& let) = 0;
  virtual T visit(AST::Path& path) = 0;
  virtual T visit(AST::PathSegment& segment) = 0;
  virtual T visit(Expr& expr) = 0;
  virtual T visit(Lit& lit) = 0;
  virtual T visit(Call& call) = 0;
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
  void visit(const AST::Path& path) override {
    for (const auto& segment : path.segments) {
      visit(segment);
    }
  }
  void visit(const AST::PathSegment& segment) override {
  }
  void visit(const Expr& expr) override {
    std::visit(overloaded {
      [this](const P<Block>& block) { visit(*block); },
      [this](const Lit& lit) { visit(lit); },
      [this](const P<Binary>& binary) { visit(*binary->lhs); visit(*binary->rhs); },
      [this](const AST::Path& path) { visit(path); },
      [this](const P<Call>& call) { visit(*call); },
    }, expr.kind);
  }
  void visit(const Lit& lit) override {

  }

  void visit(const Call& call) override {

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
  void visit(AST::Path& path) override {
    for (auto& segment : path.segments) {
      visit(segment);
    }
  }
  void visit(AST::PathSegment& segment) override {
  }
  void visit(Expr& expr) override {
    std::visit(overloaded {
      [this](P<Block>& block) { visit(*block); },
      [this](Lit& lit) { visit(lit); },
      [this](P<Binary>& binary) { visit(*binary->lhs); visit(*binary->rhs); },
      [this](AST::Path& path) { visit(path); },
      [this](P<Call>& call) { visit(*call); },
    }, expr.kind);
  }
  void visit(Lit& lit) override {

  }

  void visit(Call& call) override {

  }
};
}
