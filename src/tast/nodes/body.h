#pragma once
#include "../tast_node.h"
#include "nodes/core.h"
#include "nodes/expr.h"

namespace TAST {
  struct FnDef;
  struct Item;

  /*
  * namespace for bodies
  */
  struct NS {
    std::vector<AST::Ident> segments;
    // TODO: implement < and == operators
    bool operator<(const NS &o)  const {
      for (size_t i = 0; i < segments.size(); i++) {
        if (segments[i].identifier != o.segments[i].identifier) {
          return false;
        }
      }
      return true;
    }
  };

  struct Body {
    std::vector<P<Expr>> params;
    P<Expr> expr;
  };

  /**
  * Contains all executable parts of the program (functions, consts) indexed by their
  * global path (e.g. for a function inside `main`: `main::function`)
  */
  struct Crate {
    std::map<NS, P<Body>> bodies;
  };
}
