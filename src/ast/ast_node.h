#pragma once

#include <cstdint>
#include <spdlog/spdlog.h>

#include <cmath>
#include <string>
#include <variant>
#include <vector>

#include "nodes/core.h"

// forward declare structs for circular dependencies
namespace AST {
struct Block;
struct Stmt;
struct Lit;
struct Expr;
}

#include "nodes/expr.h"
#include "nodes/item.h"
#include "nodes/stmt.h"
