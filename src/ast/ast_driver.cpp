#include "ast_driver.h"
#include "visitors/print_visitor.h"

ASTDriver::ASTDriver(Scanner* scanner)
    : scanner(scanner)
    , parser(*this, *scanner)
{
}

void ASTDriver::parse()
{
  this->parser.parse();
  AST::PrintVisitor visitor;
  visitor.Visitor::visit(std::move(this->ast.value()));
}

P<Driver> ASTDriver::execute()
{
  parse();
  return nullptr;
}
