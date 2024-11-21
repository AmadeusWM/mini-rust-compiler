#pragma once

#include "../tast_node.h"
#include "util.h"
#include <variant>
namespace TAST {
  struct Let;
  struct Expr;
  struct Item;

  typedef std::variant<
      P<Let>,
      P<Expr>,
      P<Item>
      // Semi
      // Empty
      >
      StmtKind;

  struct Stmt {
    NodeId id;
    StmtKind kind;
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
        Pat pat;
        LocalKind kind;
      };
}
