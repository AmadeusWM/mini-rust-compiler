#pragma once

#include "nodes/core.h"
#include <variant>

namespace AST {
  struct Infer{};
  struct Unit{};

  typedef std::variant<
    Path,
    Infer,
    Unit
  > TyKind;

  struct Ty {
    TyKind kind;
  };
}
