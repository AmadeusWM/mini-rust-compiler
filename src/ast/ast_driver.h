#pragma once

#include "parser/parser.h"
#include "lexer/scanner.h"
#include "node.h"

namespace MRI {
class ASTDriver {
    public:
        AST::Crate* ast = nullptr;
        MRI::Scanner* scanner;
        MRI::Parser parser;
        ASTDriver(MRI::Scanner* scanner);
        void parse();
};
}
