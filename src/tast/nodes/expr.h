#pragma once
#include "util/util.h"
#include "../tast_node.h"
#include "../../ast/ast_node.h"
#include "type.h"

namespace TAST {
  struct Binary;
  struct Unary;
  struct Call;
  struct Ret;
  struct Break;
  struct If;
  struct Loop;
  struct Assign;
  struct Print;

  struct Lit {
    NodeId id;
    // potentially add:
    // - suffix
    // - symbol
    Ty ty;
    AST::LitKind kind;
  };

  typedef std::variant<
    // Path,
    Break,
    Lit,
    AST::Ident,
    P<Print>,
    P<Loop>,
    P<If>,
    P<Ret>,
    P<Block>,
    P<Binary>,
    P<Unary>,
    P<Assign>,
    P<Call>
  > ExprKind;


  struct Print {
    NodeId id;
    AST::PrintKind kind;
  };

  struct Ret {
    NodeId id;
    P<Expr> expr;
  };

  struct Break{
    NodeId id;
  };

  struct Expr {
    NodeId id;
    ExprKind kind;
    Ty ty;
  };

  struct Assign {
    NodeId id;
    AST::Ident lhs;
    P<Expr> rhs;
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

  struct Binary {
    NodeId id;
    AST::BinOp op;
    P<Expr> lhs;
    P<Expr> rhs;
    Ty ty;
  };

  struct Unary {
    NodeId id;
    AST::UnOp op;
    P<Expr> expr;
    Ty ty;
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
