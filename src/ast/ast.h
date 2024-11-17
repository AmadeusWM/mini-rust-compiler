#pragma once

#include <memory>

#include "node.h"
class AST {
    public:
        AST(ProgramNode root)
        : root(std::move(root)) {}
        ProgramNode root;
};
