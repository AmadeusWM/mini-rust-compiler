#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <variant>

#include "nodes/core.h"

/**
* The typed AST
*/
namespace TAST {
struct Block;
struct Stmt;
struct Lit;
struct Expr;
}

#include "nodes/expr.h"
#include "nodes/body.h"
#include "nodes/stmt.h"
