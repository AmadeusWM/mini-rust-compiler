#pragma once
#include "util/util.h"
#include "../tast_node.h"
#include "type.h"

namespace TAST {
  struct Binary;

  typedef std::variant<
    // Path,
    Lit,
    Path,
    P<Block>,
    P<Binary>
  > ExprKind;

  struct Expr {
    NodeId id;
    ExprKind kind;
    Ty ty;
  };

  struct Binary {
    AST::BinOp op;
    P<Expr> lhs;
    P<Expr> rhs;
  };

  struct Block {
    NodeId id;
    std::vector<P<Stmt>> statements;
    // optional expression at the end of the block for implicit return
    Opt<P<Expr>> expr;
  };
}
