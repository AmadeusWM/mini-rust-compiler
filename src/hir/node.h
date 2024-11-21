#pragma once

/**
* The typed AST
*/
#include <cstdint>
#include <map>
#include <string>
#include <vector>
namespace TAST {
  typedef uint64_t NodeId;

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

  struct Body {
    std::vector<int> params;
    int expr;
  };

  /**
  * Contains all executable parts of the program (functions, consts) indexed by their
  * global path (e.g. for a function inside `main`: `main::function`)
  */
  typedef std::map<Path, Body> BodyMap;
}
