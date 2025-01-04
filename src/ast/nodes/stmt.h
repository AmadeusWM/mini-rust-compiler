#pragma once

#include "../ast_node.h"
#include "nodes/type.h"
#include "util.h"
#include <variant>
namespace AST {
  struct Let;
  struct Expr;
  struct Item;
  struct Semi;

  typedef std::variant<
      P<Let>,
      P<Expr>,
      P<Item>,
      P<Semi>
      // Empty
      >
      StmtKind;

  struct Stmt {
    NodeId id;
    StmtKind kind;
  };

  struct Semi {
    P<Expr> expr;
  };

  struct Decl { };

  typedef std::variant<
      Decl, // declaration
      P<Expr> // init
      // InitElse ???? nah, i'm not deranged
      >
      LocalKind;

  struct Let {
    NodeId id;
    P<Pat> pat;
    P<Ty> ty;
    LocalKind kind;
    bool mut;
  };
}
