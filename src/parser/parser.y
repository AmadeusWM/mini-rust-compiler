%{
//#include "../lexer/includes.h"
#include <iostream>
#include <cstdio>

// C-declarations
extern "C" int yylex();
void yyerror(const char *s);
%}
%defines
%union {
    int integer;
    char *string_literal;
}
// Yacc declarations
// keywords: https://doc.rust-lang.org/reference/keywords.html
%token KW_AS KW_BREAK KW_CONST KW_CONTINUE KW_CRATE KW_ELSE KW_ENUM KW_EXTERN KW_FALSE KW_FN KW_FOR KW_IF KW_IMPL KW_IN KW_LET KW_LOOP KW_MATCH KW_MOD KW_MOVE KW_MUT KW_PUB KW_REF KW_RETURN KW_SELFVALUE KW_SELFTYPE KW_STATIC KW_STRUCT KW_SUPER KW_TRAIT KW_TRUE KW_TYPE KW_UNSAFE KW_USE KW_WHERE KW_WHILE KW_ASYNC KW_AWAIT KW_DYN KW_ABSTRACT KW_BECOME KW_BOX KW_DO KW_FINAL KW_MACRO KW_OVERRIDE KW_PRIV KW_TYPEOF KW_UNSIZED KW_VIRTUAL KW_YIELD KW_TRY

// punctiations: https://doc.rust-lang.org/reference/tokens.html#punctuation
%token PLUS MIN STAR SLASH PERCENT CARET NOT AND OR AND_AND OR_OR SHL SHR PLUS_EQ MINUS_EQ STAR_EQ SLASH_EQ PERCENT_EQ CARET_EQ AND_EQ OR_EQ SHL_EQ SHR_EQ EQ EQ_EQ NE GT LT GE LE AT UNDERSCORE DOT DOT_DOT DOT_DOT_DOT DOT_DOT_EQ COMMA SEMI COLON PATH_SEP R_ARROW FAT_ARROW L_ARROW POUND DOLLAR QUESTION TILDE

%left PLUS MIN
%left STAR SLASH PERCENT

// brackets
%token L_PAREN R_PAREN L_BRACE R_BRACE L_BRACKET R_BRACKET

// identifiers: https://doc.rust-lang.org/reference/identifiers.html
// literals: https://doc.rust-lang.org/reference/tokens.html#literals
%token <string_literal> IDENTIFIER <integer> INTEGER_LITERAL <string_literal> STRING_LITERAL

// custom
%token PRINT
%%
// productions
program:
    statements
    ;

statements:
    statements statement
    | statement
    ;

statement:
    declaration SEMI { std::cout << "Declaration" << std::endl; }
    | print_statement SEMI { std::cout << "Print statement" << std::endl; }
    | function_definition { std::cout << "Function definition" << std::endl; }
    ;

function_definition:
    KW_FN IDENTIFIER L_PAREN R_PAREN block { std::cout << "Function definition" << std::endl; }
    ;

block:
    L_BRACE statements R_BRACE { std::cout << "Block" << std::endl; }
    ;

declaration:
    KW_LET IDENTIFIER EQ INTEGER_LITERAL { std::cout << "Variable " << $2 << " to " << $4 << std::endl; }
    ;

print_statement:
    PRINT L_PAREN STRING_LITERAL R_PAREN { std::cout << "Print string " << $3 << std::endl; }
    | PRINT L_PAREN IDENTIFIER R_PAREN { std::cout << "Print variable" << std::endl; }
    | error;
%%

void yyerror(const char *s) {
  std::cerr << "Error: " << s << std::endl;
}
