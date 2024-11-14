// #include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/mri_scanner.h"
#include <cstdio>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);

  MRI::Scanner scanner(&file);
  MRI::Parser parser(scanner);
  parser();
}
