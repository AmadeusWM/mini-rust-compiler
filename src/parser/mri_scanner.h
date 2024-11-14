#pragma once
// #if ! defined(yyFlexLexerOnce)
// #undef yyFlexLexer
// #define yyFlexLexer MRI_FlexLexer // the trick with prefix; no namespace here :(
// #include <FlexLexer.h>
// #endif

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL MRI::Parser::symbol_type MRI::Scanner::get_next_token()

#include "parser.h"

namespace MRI {
class Scanner : public yyFlexLexer {
  public:
      Scanner(std::istream *in) : yyFlexLexer(in)
      {
      };
      virtual ~Scanner() {};

      // virtual Parser::symbol_type yylex( Parser::semantic_type* const yylval, Parser::location_type* yylloc );
      virtual MRI::Parser::symbol_type get_next_token();
         // Method body created by flex in lexer.cpp
  private:
     /* yyval ptr */
     Parser::semantic_type *yylval = nullptr;
  };
}