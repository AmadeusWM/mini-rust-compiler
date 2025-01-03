#pragma once
#include "nodes/core.h"
#include "util/util.h"
#include "../ast_node.h"
#include <bits/types/wint_t.h>

namespace AST {
  struct Block;
  struct Binary;
  struct Call;
  struct Ret;
  struct If;
  struct Loop;
  struct While;

  typedef std::variant<
    Lit,
    Path,
    Break,
    P<If>,
    P<While>,
    P<Loop>,
    P<Block>,
    P<Binary>,
    P<Ret>,
    P<Call>
  > ExprKind;

  struct Ret {
    NodeId id;
    P<Expr> expr;
  };

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

  struct While {
    NodeId id;
    P<Expr> cond;
    P<Block> block;
  };

  struct If {
    NodeId id;
    P<Expr> cond;
    P<Block> then_block;
    Opt<P<Expr>> else_block;
  };

  struct Loop {
    NodeId id;
    P<Block> block;
  };

  struct Call {
    NodeId id;
    Path path; // NOTE: no support for calling functions that are stored in variables etc.
    std::vector<P<Expr>>params;
  };
}
