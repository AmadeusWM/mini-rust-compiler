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
    P<Pat> pat;
    P<Ty> ty;
    bool mut;
  };

  struct FnSig {
    NodeId id;
    std::vector<P<Param>> inputs;
    P<Ty> output;
  };

  struct FnDef {
    NodeId id;
    Ident ident;
    P<FnSig> signature;
    P<AST::Block> body;
  };
}
