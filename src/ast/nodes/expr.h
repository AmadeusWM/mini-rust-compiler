#pragma once
#include "util/util.h"
#include "../ast_node.h"
#include <bits/types/wint_t.h>

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
    std::vector<P<Stmt>> statements;
  };
}
