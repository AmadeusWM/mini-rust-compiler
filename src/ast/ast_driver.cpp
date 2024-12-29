#include "ast_driver.h"
#include "visitors/lower_ast_visitor.h"
#include "visitors/name_resolution_visitor.h"
#include "visitors/namespace_tree_builder.h"
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
}

P<Driver> ASTDriver::execute()
{
  parse();
  AST::NamespaceTreeBuilder ns_builder;
  ns_builder.visit(*this->ast.value());

  AST::NameResolutionVisitor visitor(ns_builder.namespace_tree);
  visitor.visit(*this->ast.value());

  AST::LowerAstVisitor lowerer(visitor.namespace_tree);
  lowerer.visit(*this->ast.value());
  // auto crate = lower();
  return nullptr;
  // return P<TASTDriver>(new TASTDriver(std::move(crate)));
}

AST::NodeId ASTDriver::create_node() {
  return this->curr_id++;
}
