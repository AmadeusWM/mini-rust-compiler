#include "ast_driver.h"
#include "tast_driver.h"
#include "visitors/lower_ast_visitor.h"
#include "visitors/name_resolution_visitor.h"
#include "visitors/print_visitor.h"

ASTDriver::ASTDriver(Scanner* scanner)
    : scanner(scanner)
    , rules(P<ParserRules>(new ParserRules(*this)))
    , parser(*this, *scanner)
{}

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
  auto crate = lower();
  return P<TASTDriver>(new TASTDriver(std::move(crate)));
}

AST::NodeId ASTDriver::create_node() {
  return this->curr_id++;
}

P<TAST::Crate> ASTDriver::lower() {
  spdlog::info("Lowering to TAST...");
  AST::LowerAstVisitor visitor;
  return visitor.lower_crate(*this->ast.value());
}
