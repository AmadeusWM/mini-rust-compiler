#pragma once

#include "parser.h"
#include "../lexer/scanner.h"

namespace MRI {
class Driver {
    public: 
        MRI::Scanner* scanner;
        MRI::Parser parser;
        Driver(MRI::Scanner* scanner);
        void parse();
};
}