#include "driver.h"

MRI::Driver::Driver(MRI::Scanner* scanner) 
    : scanner(scanner), parser(*this, *scanner)
{
}

void MRI::Driver::parse() {
    this->parser.parse();
}
