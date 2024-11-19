#pragma once

#include "lexer/scanner.h"
#include "node.h"
#include "parser/parser.h"
#include "../driver.h"
#include <optional>

class ASTDriver : public Driver {
public:
  Opt<AST::Crate> ast = std::nullopt;
  Scanner *scanner;
  MRI::Parser parser;

  ASTDriver(Scanner *scanner);

  void parse();

  P<Driver> execute() override;
  std::string name() override { return "AST Driver"; }
};
