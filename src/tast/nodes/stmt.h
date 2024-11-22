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
      P<Expr>
      // Semi
      // Empty
      >
      StmtKind;

  struct Stmt {
    NodeId id;
    StmtKind kind;
  };

  struct Decl { };

  struct Let {
    NodeId id;
    // let <PAT> = 5;
    Pat pat;
    // let x: i32 = <INIT>;
    Opt<P<Expr>> initializer;
  };
}
