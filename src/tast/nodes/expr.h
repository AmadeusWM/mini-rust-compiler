#pragma once
#include "util/util.h"
#include "../tast_node.h"

namespace TAST {
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
    // optional expression at the end of the block for implicit return
    Opt<Expr> expr;
  };
}
