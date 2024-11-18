#include "ast_driver.h"

MRI::ASTDriver::ASTDriver(MRI::Scanner* scanner)
    : scanner(scanner), parser(*this, *scanner)
{
}

void MRI::ASTDriver::parse() {
    this->parser.parse();
    PrintVisitor visitor;
    visitor.visit(std::move(this->ast->root));
}
