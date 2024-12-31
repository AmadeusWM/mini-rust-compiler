#pragma once
#include "nodes/core.h"
#include "util/util.h"
#include "../ast_node.h"
#include <bits/types/wint_t.h>

namespace AST {
  struct Block;
  struct Binary;
  struct Call;

  typedef std::variant<
    Lit,
    Path,
    P<Block>,
    P<Binary>,
    P<Call>
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

  struct Call {
    NodeId id;
    Path path; // NOTE: no support for calling functions that are stored in variables etc.
    std::vector<P<Expr>>params;
  };
}
