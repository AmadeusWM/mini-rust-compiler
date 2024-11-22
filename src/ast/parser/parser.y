%language "c++"
%require  "3.2"

%code requires {
    #include "../ast_node.h"

    class Scanner;
    class ASTDriver;
}

%code top {
    #include <iostream>
    #include <string>

    #include "../lexer/scanner.h"
    #include "../ast_driver.h"
    #include "parser.h"
    #include "../../util/util.h"

    // #define YYDEBUG 1 // print ambiguous states
}

%header
%verbose
// defines: https://www.gnu.org/software/bison/manual/html_node/_0025define-Summary.html
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%define parse.error verbose

/* parameter to yylex */
%lex-param { Scanner &scanner }
%parse-param { ASTDriver &driver }
%parse-param { Scanner &scanner }

%code {
    // scanner is provided to yylex by the %lex-param directive
    static MRI::Parser::symbol_type yylex(Scanner &scanner) {
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

%type <int> crate
%type <P<AST::Crate>> function_definitions
%type <P<AST::Item>> function_definition
%type <P<AST::Block>> block
%type <P<AST::Block>> statements
%type <P<AST::Stmt>> statement
%type <P<AST::Let>> let_statement
%type <AST::LocalKind> local;
%type <P<AST::Expr>> expr
%type <P<AST::Expr>> expr_with_block
%type <P<AST::Expr>> expr_without_block
%type <P<AST::Expr>> block_expr
%type <P<AST::Expr>> literal_expr
%type <AST::Ident> ident
%type <P<AST::Expr>> ident_expr


// custom
%token PRINT

%%
// productions
crate:
    function_definitions END {
        // todo: we now parsed the program and have an AST. We
        // want to transition to the next state, so we want to
        // transition into the ASTDriverState, which takes
        // an AST as a parameter.
        // e.g.: driver.transition(ASTDriverState(ProgramNode($1)));
        driver.ast = Opt<P<AST::Crate>>(std::move($1));
        $$ = 1;
    }
    ;

function_definitions:
    function_definitions function_definition {
        $1->items.push_back(std::move($2));
        $$ = std::move($1);
    }
    | function_definition {
        $$ = driver.rules->initFunctionDefinitions(std::move($1));
    }
    ;


function_definition:
    KW_FN ident L_PAREN R_PAREN block {
        $$ = P<AST::Item>(new AST::Item {
            driver.create_node(),
            AST::ItemKind{
                P<AST::FnDef>(new AST::FnDef{
                    driver.create_node(),
                    $2,
                    std::move($5)
                })
            }
        });
    }
    ;

block:
    L_BRACE statements R_BRACE { $$ = std::move($2); }
    ;

statements:
    statements statement {
        $1->statements.push_back(std::move($2));
        $$ = std::move($1);
    }
    | statement {
        $$ = P<AST::Block>(new AST::Block {
          driver.create_node(),
        });
        $$->statements.push_back(std::move($1));
    }
    ;

statement:
    let_statement {
        $$ = P<AST::Stmt>(new AST::Stmt {
          driver.create_node(),
          std::move($1)
        });
    }
    | expr_without_block SEMI {
        $$ = P<AST::Stmt>(new AST::Stmt{
          driver.create_node(),
          std::move($1)
        });
    }
    | expr_with_block SEMI {
        $$ = P<AST::Stmt>(new AST::Stmt{
          driver.create_node(),
          std::move($1)
        });
    }
    | expr_with_block {
        $$ = P<AST::Stmt>(new AST::Stmt{
          driver.create_node(),
          std::move($1)
        });
    }
    ;


let_statement:
    KW_LET ident local SEMI {
        $$ = P<AST::Let>(new AST::Let {
            .id = driver.create_node(),
            .pat = AST::Pat($2),
            .kind = std::move($3)
        });
    }
    ;

local:
    EQ expr {
        $$ = AST::LocalKind(std::move($2));
    }
    | { $$ = AST::LocalKind(AST::Decl {}); }
    ;

expr:
    expr_without_block { $$ = std::move($1); }
    | expr_with_block { $$ = std::move($1); }
    ;

expr_without_block:
    literal_expr { $$ = std::move($1); }
    | ident_expr { $$ = std::move($1); }
    ;


expr_with_block:
    block_expr { $$ = std::move($1); }
    ;
;

ident:
    IDENTIFIER {
        $$ = AST::Ident{
          .identifier = $1
        };
    }
    ;

block_expr:
    block {
        $$ = P<AST::Expr>(new AST::Expr {
            driver.create_node(),
            AST::ExprKind {
                std::move($1)
            }
        });
    }
    ;

ident_expr:
    IDENTIFIER {
      $$ = P<AST::Expr>(new AST::Expr {
        driver.create_node(),
        AST::ExprKind {
          AST::Path {
            .segments = std::vector<AST::PathSegment>{AST::PathSegment {
              driver.create_node(),
              AST::Ident {
                $1
              }
            }}
          }
        }
      });
    }
    ;

literal_expr:
    INTEGER_LITERAL {
        $$ = P<AST::Expr>(new AST::Expr {
            driver.create_node(),
            AST::ExprKind {
                AST::Lit{
                  driver.create_node(),
                  AST::LitKind($1)
                }
            }
        });
    }
    ;

%%

void MRI::Parser::error(const location &loc , const std::string &message) {
	std::cout << "Error"
        << "(" << loc << "): "
        << message << std::endl;
}
