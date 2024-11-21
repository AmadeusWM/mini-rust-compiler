#pragma once
#include "util/util.h"
#include "../node.h"

namespace AST {
  struct Block;

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

  struct Block {
    NodeId id;
    std::vector<Stmt> statements;
  };
}
