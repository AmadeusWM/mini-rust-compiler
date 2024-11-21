#pragma once

#include "lexer/scanner.h"
#include "tast_node.h"
#include "parser/parser.h"
#include "../driver.h"
#include <optional>

class TASTDRiver : public Driver {
private:
  AST::NodeId curr_id = 0;

public:
  Opt<AST::Crate> ast = std::nullopt;
  Scanner *scanner;
  MRI::Parser parser;

  TASTDRiver(Scanner *scanner);

  void parse();
  void nameResolution();

  P<Driver> execute() override;
  std::string name() override { return "TAST Driver"; }

  AST::NodeId create_node() {
    return curr_id++;
  }
};
