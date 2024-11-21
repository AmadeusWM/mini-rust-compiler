#pragma once
#include "../node.h"

namespace AST {
  struct FnDef;
  struct Item;

  struct Crate {
    NodeId id;
    std::vector<Item> items;
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

  struct FnDef {
    NodeId id;
    Ident ident;
    P<AST::Block> body;
  };
}
