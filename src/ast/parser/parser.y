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
%type <P<AST::Crate>> items
%type <P<AST::Item>> item
%type <P<AST::FnDef>> function_definition
%type <P<AST::FnSig>> function_signature
%type <Vec<P<AST::Param>>> params
%type <P<AST::Param>> param
%type <P<AST::Block>> block
%type <P<AST::Block>> statements
%type <P<AST::Stmt>> statement
%type <P<AST::Ret>> ret
%type <P<AST::Let>> let
%type <AST::LocalKind> local_kind;
%type <P<AST::Expr>> expr
%type <P<AST::Expr>> expr_with_block
%type <P<AST::Expr>> expr_without_block
%type <AST::Lit> literal
%type <AST::Ident> ident
%type <AST::Path> path
%type <P<AST::Binary>> binary
%type <AST::BinOp> bin_op
%type <P<AST::Pat>> pat
%type <P<AST::Ty>> type
%type <P<AST::Ty>> local_type
%type <P<AST::Call>> call


// custom
%token PRINT

%%
// productions
crate:
    items END {
        // todo: we now parsed the program and have an AST. We
        // want to transition to the next state, so we want to
        // transition into the ASTDriverState, which takes
        // an AST as a parameter.
        // e.g.: driver.transition(ASTDriverState(ProgramNode($1)));
        driver.ast = Opt<P<AST::Crate>>(std::move($1));
        $$ = 1;
    }
    ;

items:
    items item { $$ = driver.rules->addItem(std::move($1), std::move($2)); }
    | item { $$ = driver.rules->initItems(std::move($1)); }
    | { $$ = driver.rules->initItems(); }
    ;


item:
    function_definition { $$ = driver.rules->item(std::move($1)); }
    ;

function_definition:
    KW_FN ident function_signature block {
        $$ = driver.rules->functionDefinition(std::move($2), std::move($3), std::move($4));
    }
    ;

function_signature:
  L_PAREN params R_PAREN R_ARROW type { $$ = driver.rules->functionSignature(std::move($2), std::move($5)); }
  | L_PAREN params R_PAREN { $$ = driver.rules->functionSignature(std::move($2), P<AST::Ty>(new AST::Ty{AST::Unit{}})); }
  ;
params:
    params COMMA param { $$ = driver.rules->addParam(std::move($1), std::move($3)); }
    | param { $$ = driver.rules->initParams(std::move($1)); }
    | { $$ = driver.rules->initParams(); }
    ;

param:
  pat COLON type { $$ = driver.rules->param(std::move($1), std::move($3)); }
  ;

type:
    path { $$ = driver.rules->ty(std::move($1)); }
    ;

block:
    L_BRACE statements R_BRACE { $$ = std::move($2); }
    ;

statements:
    statements expr_without_block { $$ = driver.rules->addStatement(std::move($1), driver.rules->statement(std::move($2))); }
    | statements statement { $$ = driver.rules->addStatement(std::move($1), std::move($2)); }
    | statement { $$ = driver.rules->initStatements(std::move($1)); }
    | { $$ = driver.rules->initStatements(); }
    ;

statement:
    let { $$ = driver.rules->statement(std::move($1)); }
    | item { $$ = driver.rules->statement(std::move($1)); }
    | expr_without_block SEMI { $$ = driver.rules->statement(driver.rules->semi(std::move($1))); }
    | expr_with_block SEMI { $$ = driver.rules->statement(driver.rules->semi(std::move($1))); }
    | expr_with_block { $$ = driver.rules->statement(std::move($1)); }
    ;

ret:
    KW_RETURN expr SEMI { $$ = driver.rules->ret(std::move($2)); }
    ;

binary:
    expr bin_op expr { $$ = driver.rules->binary(std::move($1), $2, std::move($3)); }
    ;

bin_op:
    PLUS { $$ = AST::Bin::Add{}; }
    | MIN { $$ = AST::Bin::Sub{}; }
    ;


let:
    KW_LET pat local_type local_kind SEMI { $$ = driver.rules->let(std::move($2), std::move($3), std::move($4)); }
    ;

local_kind:
    EQ expr { $$ = std::move($2); }
    | { $$ = AST::Decl {}; }
    ;

local_type:
    COLON type { $$ = std::move($2); }
    | { $$ = driver.rules->ty(AST::TyKind(AST::Infer {})); }


expr:
    expr_without_block { $$ = std::move($1); }
    | expr_with_block { $$ = std::move($1); }
    ;

expr_without_block:
    binary { $$ = driver.rules->expr(std::move($1)); }
    | literal { $$ = driver.rules->expr(std::move($1)); }
    | path { $$ = driver.rules->expr(std::move($1)); }
    | call { $$ = driver.rules->expr(std::move($1)); }
    | ret { $$ = driver.rules->expr(std::move($1)); }
    ;

expr_with_block:
    block { $$ = driver.rules->expr(std::move($1)); }
    ;
;

call:
    path L_PAREN R_PAREN { $$ = driver.rules->call(std::move($1), std::vector<P<AST::Expr>>{}); }
    ;

pat:
    ident { $$ = driver.rules->pat(std::move($1)); }

ident:
    IDENTIFIER { $$ = driver.rules->ident($1); }
    ;

path:
    ident { $$ = driver.rules->path(std::move($1)); }
    ;

literal:
    INTEGER_LITERAL { $$ = driver.rules->lit($1); }
    ;

%%

void MRI::Parser::error(const location &loc , const std::string &message) {
	std::cout << "Error"
        << "(" << loc << "): "
        << message << std::endl;
}
