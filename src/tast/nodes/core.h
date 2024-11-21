#pragma once

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

struct Ident {
  std::string identifier;
};

struct PathSegment {
  NodeId id;
  Ident ident;
};

struct Path {
  std::vector<PathSegment> segments;
};

typedef std::variant<
    Ident>
    Pat;
}
