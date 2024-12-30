#pragma once
#include "util/util.h"
#include "../tast_node.h"
#include "../../ast/ast_node.h"
#include "type.h"

namespace TAST {
  struct Binary;
  struct Call;

  typedef std::variant<
    // Path,
    Lit,
    AST::Ident,
    P<Block>,
    P<Binary>,
    P<Call>
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

  struct Call {
    NodeId id;
    NodeId callee;
    std::vector<P<Expr>> params;
  };

  struct Block {
    NodeId id;
    std::vector<P<Stmt>> statements;
    // optional expression at the end of the block for implicit return
    Opt<P<Expr>> expr;
  };
}
