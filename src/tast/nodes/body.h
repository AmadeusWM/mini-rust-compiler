#pragma once
#include "../tast_node.h"
#include "nodes/type.h"

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
    std::map<NodeId, P<Body>> bodies;
  };
}
