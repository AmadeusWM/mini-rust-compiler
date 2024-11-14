%require  "3.0"
%skeleton "lalr1.cc" 

%code requires {

    namespace MRI {
        class Scanner;
        // class Driver;
    }
}

%code top {
    #include <iostream>

    #include "mri_scanner.h"
    #include "parser.h"
    #include "location.hh"
}

%header
%verbose
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%lex-param { MRI::Scanner &scanner }
%parse-param { MRI::Scanner &scanner }

%code {
    static MRI::Parser::symbol_type yylex(MRI::Scanner &scanner) {
        return scanner.get_next_token();
    }
    // #define yylex(x, y) scanner.get_next_token()
}

%define api.parser.class { Parser }
%define api.namespace { MRI }
%locations

%defines
// Yacc declarations
%token END

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
%token IDENTIFIER INTEGER_LITERAL STRING_LITERAL

// custom
%token PRINT

%start program

%%
// productions
program:
    KW_AS { std::cout << "AS" << std::endl; };
%%

// Bison expects us to provide implementation - otherwise linker complains
void MRI::Parser::error(const location &loc , const std::string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	std::cout << "Error: " << message << std::endl << "Location: " << loc << std::endl;
}
