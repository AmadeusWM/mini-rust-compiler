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
    P<Expr>,
    P<Item>
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

struct Ident {
  std::string identifier;
};

struct PathSegment {
  NodeId id;
  Ident ident;
};

struct Path {
  std::vector<PathSegment> segments;
};

typedef std::variant<
  Ident
> Pat;

struct Let {
  NodeId id;
  Pat pat;
  LocalKind kind;
};

typedef std::variant<
  // Path,
  Lit,
  Path,
  P<Block>
> ExprKind;

struct Expr {
  NodeId id;
  ExprKind kind;
};

struct FnDef {
  NodeId id;
  Ident ident;
  P<Block> body;
};

struct Block {
  NodeId id;
  std::vector<Stmt> statements;
};
}
