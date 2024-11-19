#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL MRI::Parser::symbol_type Scanner::get_next_token()

#include "../parser/parser.h"

class Scanner : public yyFlexLexer {
public:
  Scanner(std::istream *in) : yyFlexLexer(in){};
  virtual ~Scanner(){};

  virtual MRI::Parser::symbol_type get_next_token();
  // Method body created by flex in lexer.cpp
private:
  MRI::Parser::location_type yylloc{};
};
