#pragma once
#include "util/util.h"
#include "../ast_node.h"
#include <bits/types/wint_t.h>

namespace AST {
  struct Block;
  struct Binary;

  typedef std::variant<
    Lit,
    Path,
    P<Block>,
    P<Binary>
  > ExprKind;

  struct Expr {
    NodeId id;
    ExprKind kind;
  };

  namespace Bin {
    struct Add{};
    struct Sub{};
  }

  typedef std::variant<
    Bin::Add,
    Bin::Sub
  > BinOp;

  struct Binary {
    BinOp op;
    P<Expr> lhs;
    P<Expr> rhs;
  };

  struct Block {
    NodeId id;
    std::vector<P<Stmt>> statements;
  };
}
