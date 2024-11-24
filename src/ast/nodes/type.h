#pragma once

#include "nodes/core.h"
#include <variant>

namespace AST {
  struct Infer{};

  typedef std::variant<
    Path,
    Infer
  > TyKind;

  struct Ty {
    NodeId id;
    TyKind kind;
  };
}
