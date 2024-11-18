#include "ast_driver.h"

MRI::ASTDriver::ASTDriver(MRI::Scanner* scanner)
    : scanner(scanner), parser(*this, *scanner)
{
}

void MRI::ASTDriver::parse() {
    this->parser.parse();
    AST::PrintVisitor visitor;
    visitor.Visitor::visit(*std::move(this->ast));
}
