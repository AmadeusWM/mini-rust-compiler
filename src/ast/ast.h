#pragma once

#include <memory>

#include "node.h"
class AST {
    public:
        AST(Crate root)
        : root(std::move(root)) {}
        Crate root;
};
