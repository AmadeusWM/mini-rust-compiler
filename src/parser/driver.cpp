#include "driver.h"

MRI::Driver::Driver(MRI::Scanner* scanner)
    : scanner(scanner), parser(*this, *scanner)
{
}

void MRI::Driver::parse() {
    this->parser.parse();
    PrintVisitor visitor;
    visitor.visit(Node(std::move(this->ast->root)));
}
