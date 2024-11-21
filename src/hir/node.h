#pragma once

/**
* The typed AST
*/
#include <vector>
namespace TAST {

  struct Body {
    std::vector<int> params;
    int expr;
  };
}
