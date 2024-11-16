
#include "node.h"
class AST {
    public:
        AST(ProgramNode root)
        : root(root) {}
        ProgramNode root;
};
