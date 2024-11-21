#pragma once
#include "../tast_node.h"
#include "nodes/expr.h"

namespace TAST {
  struct FnDef;
  struct Item;

  struct Body {
    std::vector<P<Expr>> params;
    P<Expr> expr;
  };

  /**
  * Contains all executable parts of the program (functions, consts) indexed by their
  * global path (e.g. for a function inside `main`: `main::function`)
  */
  typedef std::map<Path, Body> Crate;
}
