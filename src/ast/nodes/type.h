#pragma once

#include "nodes/core.h"
#include <variant>

namespace AST {
  struct Infer{};
  struct Unit{};
  struct Str{};

  typedef std::variant<
    Path,
    Infer,
    Str,
    Unit
  > TyKind;

  struct Ty {
    TyKind kind;
  };
}
