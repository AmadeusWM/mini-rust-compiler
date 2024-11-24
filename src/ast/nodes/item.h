#pragma once
#include "../ast_node.h"
#include "nodes/core.h"
#include "nodes/type.h"

namespace AST {
  struct FnDef;
  struct Item;

  struct Crate {
    NodeId id;
    std::vector<P<Item>> items;
  };

  typedef std::variant<
      P<FnDef>
      // Modules
      // Type definitions
      // Use declarations
      >
      ItemKind;

  struct Item {
    NodeId id;
    ItemKind kind;
  };

  struct Param {
    NodeId id;
    P<PatKind> pat;
    P<Ty> ty;
  };

  struct FnSig {
    std::vector<P<Ty>> inputs;
    P<Ty> output;
  };

  struct FnDef {
    NodeId id;
    Ident ident;
    P<AST::Block> body;
  };
}
