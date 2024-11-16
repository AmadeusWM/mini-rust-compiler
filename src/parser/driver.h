#pragma once

#include "parser.h"
#include "../ast/ast.h"
#include "../lexer/scanner.h"

namespace MRI {
class Driver {
    public:
        AST* ast = nullptr;
        MRI::Scanner* scanner;
        MRI::Parser parser;
        Driver(MRI::Scanner* scanner);
        void parse();
};
}
