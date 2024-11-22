#include "parser_rules.h"

ParserRules::ParserRules(ASTDriver* driver) : driver{driver} {}

P<AST::Crate> ParserRules::initFunctionDefinitions(P<AST::Item> $1) {
    auto a = P<AST::Crate>(new AST::Crate{
      driver->create_node(),
    });
    a->items.push_back(std::move($1));
    return a;
}
