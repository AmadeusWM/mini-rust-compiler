// #include "lexer/lexer.h"
#include "parser/parser.h"
#include <cstdio>
#include <iostream>

int main(int argc, char *argv[]) {
  // FILE *myfile = fopen(argv[1], "r");
  // if (!myfile) {
  //   std::cout << "I can't open the file!" << std::endl;
  //   return -1;
  // }

  // yyin = myfile;

  int result = yyparse();

  return result;
}
