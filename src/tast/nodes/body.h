#pragma once
#include "../tast_node.h"
#include "namespace_tree.h"
#include "nodes/core.h"
#include "nodes/expr.h"

namespace TAST {
  /*
  * namespace for bodies
  */

  struct Param {
    NodeId id;
    P<Pat> pat;
    P<Ty> ty;
  };

  struct Body {
    std::vector<P<Param>> params;
    P<Expr> expr;
  };

  /**
  * Contains all executable parts of the program (functions, consts) indexed by their
  * global path (e.g. for a function inside `main`: `main::function`)
  */
  struct Crate {
    std::map<std::string, P<Body>> bodies;
  };
}
