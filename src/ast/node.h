#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

struct Crate;
struct FunctionDefinition;
struct Expr;
struct Stmt;

struct Block;

template <typename T> using P = std::unique_ptr<T>;

typedef std::variant<
  // - modules
  // - type definitions
  // - function definitions
  // - use declarations
  P<FunctionDefinition>
> ItemKind;

struct Let;

typedef std::variant<
  P<Let>,
  P<Expr>
  // Item
  // Semi
  // Empty
> StmtKind;

typedef std::variant<
  int,
  std::string
> LitKind;

struct Lit {
  // potentially add:
  // - suffix
  // - symbol
  LitKind kind;
};

struct Decl {
  Lit lit;
};

typedef std::variant<
  Decl,   // declaration
  P<Expr> // init
  // InitElse ???? nah, i'm not deranged
> LocalKind;

struct Let {
  std::string identifier; // this could be a "pattern"
  LocalKind kind;
};

struct Stmt {
  StmtKind kind;
};

typedef std::variant<
  Lit,
  P<Block>
> ExprKind;


struct Expr {
  P<ExprKind> kind;
};


struct Crate {
  std::vector<FunctionDefinition> children;
};

struct Block;

struct FunctionDefinition {
  std::string identifier;
  P<Block> body;
};

struct Block {
  std::vector<Stmt> children;
};

struct AssignmentNode {
  std::string identifier;
  int value;
};

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

class Visitor {
public:
  virtual void visit(const Crate& crate) {
    for (const auto& child : crate.children) {
      visit(child);
    }
  };

  virtual void visit(const FunctionDefinition& node) {
    visit(*node.body);
  }

  virtual void visit(const Block& node) {
    for (const auto& child : node.children) {
      visit(child);
    }
  }

  virtual void visit(const Stmt& node) {
    std::visit(overloaded{
      [this] (const P<Let>& let) { visit(*let); },
      [this] (const P<Expr>& expr) { visit(*expr); }
    }, node.kind);
  }

  virtual void visit(const Let& let) {
    std::visit(overloaded{
      [this](const Decl& decl) {
        std::visit(overloaded{
          [this](const int i) { std::cout << "DECL_int" << i << std::endl; },
          [this](const std::string& s) { std::cout << "DECL_str" << s << std::endl; }
        }, decl.lit.kind);
      },
      [this](const P<Expr>& expr) { visit(*expr); }
    }, let.kind);
  }

  virtual void visit(const Expr& expr) {
    std::visit(overloaded{
      [this](const Lit& lit) {
        std::visit(overloaded{
          [this](const int i) { std::cout << "LIT_int" << i << std::endl; },
          [this](const std::string& s) { std::cout << "LIT_str" << s << std::endl; }
        }, lit.kind);
      },
      [this](const P<Block>& block) { visit(*block); }
    }, *expr.kind);
  }
};

class PrintVisitor : public Visitor {
public:
  void visit(const AssignmentNode& node) override {
    std::cout << "AssignmentNode: " << node.identifier << " = " << node.value << std::endl;
  }
  void visit(const Node& node) {
    Visitor::visit(node);
  }
};
