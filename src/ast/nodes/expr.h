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
  struct Assign;
  struct Unary;

  typedef std::variant<
    Lit,
    Path,
    Break,
    P<If>,
    P<While>,
    P<Loop>,
    P<Block>,
    P<Binary>,
    P<Unary>,
    P<Ret>,
    P<Assign>,
    P<Call>
  > ExprKind;

  struct Assign {
    NodeId id;
    Ident lhs;
    P<Expr> rhs;
  };

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
    struct Mul{};
    struct Div{};
    struct Mod{};
    struct And{};
    struct Or{};
    struct Eq{};
    struct Ne{};
    struct Lt{};
    struct Le{};
    struct Gt{};
    struct Ge{};
  }

  typedef std::variant<
    Bin::Add,
    Bin::Sub,
    Bin::Mul,
    Bin::Div,
    Bin::Mod,
    Bin::And,
    Bin::Or,
    Bin::Eq,
    Bin::Ne,
    Bin::Lt,
    Bin::Le,
    Bin::Gt,
    Bin::Ge
  > BinOp;

  struct Binary {
    NodeId id;
    BinOp op;
    P<Expr> lhs;
    P<Expr> rhs;
  };

  namespace Un{
    struct Neg{};
    struct Pos{};
    struct Not{};
  }

  typedef std::variant<
    Un::Neg,
    Un::Pos,
    Un::Not
  > UnOp;

  struct Unary {
    NodeId id;
    UnOp op;
    P<Expr> expr;
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
