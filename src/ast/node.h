#pragma once

#include <cstdint>
#include <spdlog/spdlog.h>

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "../util/util.h"

namespace AST {
typedef uint64_t NodeId;

struct Crate;
struct FnDef;
struct Expr;
struct Stmt;

struct Block;
struct Item;

// TODO: Node variant that contains everything

struct Crate {
  std::vector<Item> items;
};

typedef std::variant<
    P<FnDef>
    // Modules
    // Type definitions
    // Use declarations
    >
    ItemKind;

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
    >
    StmtKind;

typedef std::variant<int, std::string> LitKind;

struct Lit {
  // potentially add:
  // - suffix
  // - symbol
  LitKind kind;
};

struct Decl { };

typedef std::variant<
    Decl, // declaration
    P<Expr> // init
    // InitElse ???? nah, i'm not deranged
    >
    LocalKind;

struct Let {
  std::string identifier; // this could be a "pattern"
  LocalKind kind;
};

struct Stmt {
  StmtKind kind;
};

typedef std::variant<Lit, P<Block>> ExprKind;

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
}
