// #include "lexer/lexer.h"
#include "ast/lexer/scanner.h"
#include "ast/ast_driver.h"
#include <cstdio>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);

  MRI::Scanner scanner(&file);
  MRI::ASTDriver driver(&scanner);
  driver.parse();
}
