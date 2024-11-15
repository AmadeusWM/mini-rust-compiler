%language "c++"
%require  "3.2"

%code requires {

    namespace MRI {
        class Scanner;
        class Driver;
    }
}

%code top {
    #include <iostream>
    #include <string>

    #include "../lexer/scanner.h"
    #include "driver.h"
    #include "parser.h"
}

%header
%verbose
// defines: https://www.gnu.org/software/bison/manual/html_node/_0025define-Summary.html
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%define parse.error verbose

/* parameter to yylex */
%lex-param { MRI::Scanner &scanner }
%parse-param { MRI::Driver &driver }
%parse-param { MRI::Scanner &scanner }

%code {
    // scanner is provided to yylex by the %lex-param directive
    static MRI::Parser::symbol_type yylex(MRI::Scanner &scanner) {
        return scanner.get_next_token();
    }
}

%define api.parser.class { Parser }
%define api.namespace { MRI }
%locations


%defines
// Yacc declarations
%token END 0

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
%token <std::string> IDENTIFIER 
%token <std::string> STRING_LITERAL
%token <int> INTEGER_LITERAL 

// custom
%token PRINT

%start program

%%
// productions
program:
    statements END { std::cout << "Program" << std::endl; }
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
    KW_LET IDENTIFIER EQ INTEGER_LITERAL {
        std::cout << "Variable " << $2 << " to " << $4 << std::endl;
    }
    ;

print_statement:
    PRINT L_PAREN STRING_LITERAL R_PAREN {
        std::cout << "Print string: " << $3 << std::endl;
    }
    | error;
%%

void MRI::Parser::error(const location &loc , const std::string &message) {
	std::cout << "Error" 
        << "(" << loc << "): " 
        << message << std::endl;
}
