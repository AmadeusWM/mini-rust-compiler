// #include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/driver.h"
#include "lexer/scanner.h"
#include <cstdio>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);

  MRI::Scanner scanner(&file);
  MRI::Driver driver(&scanner);
  driver.parse();
}
