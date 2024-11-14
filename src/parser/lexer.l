%{
#include "mri_scanner.h"

using namespace MRI;

// #undef  YY_DECL
// #define YY_DECL int Scanner::yylex( Parser::semantic_type * const yylval, Parser::location_type *yylloc )

%}

%option c++
%option yyclass="MRI::Scanner"
%option nodefault noyywrap

digit      [0-9]
identifier ([a-z]|[A-Z]|\_)([a-z]|[A-Z]|[0-9]|\_)*
FALSE      false
TRUE       true

%%

%{
    using Token = MRI::Parser::token;
%}

as        { return MRI::Parser::make_KW_AS(MRI::location()); }

<<EOF>>   { return MRI::Parser::make_END(MRI::location()); }

. {}

%%
