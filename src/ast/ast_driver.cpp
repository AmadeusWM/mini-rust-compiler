#include "ast_driver.h"
#include "tast_driver.h"
#include "visitors/lower_ast_visitor.h"
#include "visitors/name_resolution_visitor.h"
#include "visitors/namespace_tree_builder.h"
#include "visitors/print_visitor.h"
#include <spdlog/spdlog.h>

ASTDriver::ASTDriver(Scanner* scanner)
    : scanner(scanner)
    , rules(P<ParserRules>(new ParserRules(*this)))
    , parser(*this, *scanner)
{}

P<Driver> ASTDriver::execute()
{
  print_step("Parsing");
  this->parser.parse();
  AST::PrintVisitor print_visitor;
  print_visitor.Visitor::visit(*this->ast.value());

  print_step("Building Namespace Tree");
  AST::NamespaceTreeBuilder ns_builder;
  ns_builder.visit(*this->ast.value());

  print_step("Name Resolution");
  AST::NameResolutionVisitor visitor(ns_builder.namespace_tree);
  visitor.visit(*this->ast.value());

  print_step("Lowering AST");
  AST::LowerAstVisitor lowerer(visitor.namespace_tree, *this);
  lowerer.visit(*this->ast.value());

  return P<TASTDriver>(new TASTDriver(std::move(lowerer.crate)));
}

AST::NodeId ASTDriver::create_node() {
  return this->curr_id++;
}
