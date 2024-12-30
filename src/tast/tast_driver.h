#pragma once

#include "lexer/scanner.h"
#include "tast_node.h"
#include "parser/parser.h"
#include "../driver.h"

class TASTDriver : public Driver {
private:
  AST::NodeId curr_id = 0;

public:
  P<TAST::Crate> tast;

  TASTDriver(P<TAST::Crate> tast);

  void print();
  void typecheck();

  P<Driver> execute() override;
  std::string name() override { return "TAST Driver"; }
};
