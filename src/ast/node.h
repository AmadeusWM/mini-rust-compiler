#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "../util/util.h"

namespace AST {
  struct Crate;
  struct FnDef;
  struct Expr;
  struct Stmt;

  struct Block;
  struct Item;


  struct Crate {
    std::vector<Item> children;
  };

  typedef std::variant<
    P<FnDef>
    // Modules
    // Type definitions
    // Use declarations
  > ItemKind;

  struct Item {
    ItemKind kind;
  };

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
    ExprKind kind;
  };
  struct FnDef {
    std::string identifier;
    P<Block> body;
  };

  struct Block {
    std::vector<Stmt> statements;
  };

  struct AssignmentNode {
    std::string identifier;
    int value;
  };

  // static void test() {
  //   auto block = P<Block>(new Block{
  //     std::vector<Stmt>{}
  //   });

  //   auto f = P<FnDef>(new FnDef{
  //     "main",
  //     std::move(block)
  //   });
  //   auto kind = ItemKind{std::move(f)};
  //   auto item = Item{
  //     std::move(kind)
  //   };

  //   P<Crate>(new Crate{std::vector<Item>{
  //     std::move(item)
  //   }});
  // }

  class Visitor {
  public:
    virtual void visit(const Crate& crate) {
      for (const auto& child : crate.children) {
        visit(child);
      }
    };

    virtual void visit(const Item& item) {
      std::visit(overloaded{
        [this](const P<FnDef>& fn) { visit(*fn); }
      }, item.kind);
    }

    virtual void visit(const FnDef& node) {
      visit(*node.body);
    }

    virtual void visit(const Block& node) {
      for (const auto& child : node.statements) {
        visit(child);
      }
    }

    virtual void visit(const Stmt& node) {
      std::visit(overloaded{
        [this] (const P<Let>& let) {
          std::visit(overloaded{
            [this](const Decl& decl) {
              std::cout << "DECL" << std::endl;
            },
            [this](const P<Expr>& expr) { visit(*expr); }
          }, let->kind);
        },
        [this] (const P<Expr>& expr) { visit(*expr); }
      }, node.kind);
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
      }, expr.kind);
    }
  };

  class PrintVisitor : public Visitor {
  public:
    void visit(const Stmt& stmt) override {
      std::visit(overloaded{
        [this] (const P<Let>& let) {
          std::visit(overloaded{
            [this](const Decl& decl) {
              std::cout << "LET statement DECL" << std::endl;
            },
            [this](const P<Expr>& expr) {
              std::cout << "LET statement EXPR" << std::endl;
              Visitor::visit(*expr);
            }
          }, let->kind);
        },
        [this] (const P<Expr>& expr) {
          std::cout << "EXPR statement" << std::endl;
          Visitor::visit(*expr);
        }
      }, stmt.kind);
    }
  };
}
