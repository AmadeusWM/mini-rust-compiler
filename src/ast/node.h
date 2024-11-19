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
  NodeId id;
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
  NodeId id;
  ItemKind kind;
};

struct Let;

typedef std::variant<int, std::string> LitKind;

struct Lit {
  NodeId id;
  // potentially add:
  // - suffix
  // - symbol
  LitKind kind;
};

typedef std::variant<
    P<Let>,
    P<Expr>
    // Item
    // Semi
    // Empty
    >
    StmtKind;

struct Stmt {
  NodeId id;
  StmtKind kind;
};

struct Decl { };

typedef std::variant<
    Decl, // declaration
    P<Expr> // init
    // InitElse ???? nah, i'm not deranged
    >
    LocalKind;

struct Let {
  NodeId id;
  std::string identifier; // this could be a "pattern"
  LocalKind kind;
};

typedef std::variant<Lit, P<Block>> ExprKind;

struct Expr {
  NodeId id;
  ExprKind kind;
};

struct FnDef {
  NodeId id;
  std::string identifier;
  P<Block> body;
};

struct Block {
  NodeId id;
  std::vector<Stmt> statements;
};
}
