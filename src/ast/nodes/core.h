#pragma once

#include "util.h"
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace AST {
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
  Vec<std::string> to_vec() const {
    Vec<std::string> path;
    for (const auto& seg : segments) {
      path.push_back(seg.ident.identifier);
    }
    return path;
  }
  std::string to_string() const {
    std::string s = "";
    for (int i = 0; i < segments.size(); i++) {
      s += segments[i].ident.identifier;
      if (i < segments.size() - 1) {
        s += "::";
      }
    }
    return s;
  }
};

typedef std::variant<
  Ident>
  PatKind;

struct Pat {
  PatKind kind;
};
}
