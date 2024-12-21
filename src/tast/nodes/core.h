#pragma once

#include "nodes/core.h"
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace TAST {
typedef uint64_t NodeId;

typedef std::variant<int, std::string> LitKind;

struct Lit {
  NodeId id;
  // potentially add:
  // - suffix
  // - symbol
  LitKind kind;
};

typedef std::variant<
    AST::Ident>
    PatKind;

struct Pat {
  PatKind kind;
};
}
