#pragma once
#include "../ast/nodes/core.h"
#include <map>
#include <vector>

struct NS {
  std::vector<AST::Ident> segments;
  // TODO: implement < and == operators
  bool operator<(const NS &o)  const {
    for (size_t i = 0; i < segments.size(); i++) {
      if (segments[i].identifier != o.segments[i].identifier) {
        return false;
      }
    }
    return true;
  }
};

template <typename T>
class NSMap {
private:
  std::map<NS, T> store;
public:
  void insert(const NS &ns, const T &value) {
    store[ns] = value;
  }
  T lookup(const NS &ns) {
  }
};
