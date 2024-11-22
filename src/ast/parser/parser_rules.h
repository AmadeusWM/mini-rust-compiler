#pragma once
#include "../ast_node.h"
#include "../ast_driver.h"
#include "nodes/item.h"
#include "util.h"
#include <vector>

class ASTDriver;

class ParserRules {
  private:
    ASTDriver* driver;
  public:
    ParserRules(ASTDriver* driver);

    P<AST::Crate> initFunctionDefinitions(P<AST::Item> $1);
};
