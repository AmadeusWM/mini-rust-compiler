#include "ast_driver.h"
#include "visitors/name_resolution_visitor.h"
#include "visitors/print_visitor.h"

ASTDriver::ASTDriver(Scanner* scanner)
    : scanner(scanner)
    , parser(*this, *scanner)
{
}

void ASTDriver::parse()
{
  spdlog::info("Parsing...");
  this->parser.parse();
  AST::PrintVisitor visitor;
  visitor.Visitor::visit(*this->ast.value());
}

void ASTDriver::nameResolution() {
  spdlog::info("Name resolution...");
  AST::NameResolutionVisitor visitor;
  visitor.visit(*this->ast.value());
}

P<Driver> ASTDriver::execute()
{
  parse();
  nameResolution();
  return nullptr;
}
