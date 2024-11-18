#pragma once

#include "parser/parser.h"
#include "../ast/ast.h"
#include "lexer/scanner.h"

namespace MRI {
class ASTDriver {
    public:
        AST* ast = nullptr;
        MRI::Scanner* scanner;
        MRI::Parser parser;
        ASTDriver(MRI::Scanner* scanner);
        void parse();
};
}
