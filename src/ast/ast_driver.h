#pragma once

#include "lexer/scanner.h"
#include "ast_node.h"
#include "nodes/body.h"
#include "parser/parser.h"
#include "../driver.h"
#include "parser/parser_rules.h"
#include <optional>

class ParserRules;

class ASTDriver : public Driver {
private:
  AST::NodeId curr_id = 0;

public:
  Opt<P<AST::Crate>> ast = std::nullopt;
  Scanner *scanner;
  MRI::Parser parser;
  P<ParserRules> rules;

  ASTDriver(Scanner *scanner);

  void parse();
  void nameResolution();
  P<TAST::Crate> lower();

  P<Driver> execute() override;
  std::string name() override { return "AST Driver"; }

  AST::NodeId create_node();
};
