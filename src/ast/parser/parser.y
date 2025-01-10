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

// custom precedence for rules: https://www.gnu.org/software/bison/manual/html_node/Contextual-Precedence.html
%precedence KW_RETURN
%precedence EQ PLUS_EQ MINUS_EQ STAR_EQ SLASH_EQ PERCENT_EQ
%precedence U_MIN U_PLUS U_NOT
%left OR_OR
%left AND_AND
%left OR
%left AND
%left EQ_EQ NE
%left LT LE GT GE
%left SHL SHR
%left PLUS MIN
%left STAR SLASH PERCENT

// brackets
%token L_PAREN R_PAREN L_BRACE R_BRACE L_BRACKET R_BRACKET

// identifiers: https://doc.rust-lang.org/reference/identifiers.html
// literals: https://doc.rust-lang.org/reference/tokens.html#literals
%token <std::string> IDENTIFIER
%token <std::string> STRING_LITERAL
%token <int64_t> INTEGER_LITERAL
%token <double> FLOAT_LITERAL

%type <int> crate
%type <Vec<P<AST::Item>>> items
%type <P<AST::Item>> item
%type <P<AST::FnDef>> function_definition
%type <P<AST::FnSig>> function_signature
%type <Vec<P<AST::Param>>> params
%type <P<AST::Param>> param
%type <P<AST::Block>> block
%type <P<AST::Block>> statements
%type <P<AST::Block>> statements_without_expr
%type <P<AST::Stmt>> statement
%type <P<AST::Ret>> ret
%type <P<AST::Let>> let
%type <AST::LocalKind> local_kind;
%type <P<AST::Expr>> expr
%type <P<AST::Expr>> expr_with_block
%type <P<AST::Expr>> expr_without_block
%type <P<AST::Expr>> expr_without_block_raw
%type <AST::Lit> literal
%type <AST::Ident> ident
%type <AST::Path> path
%type <AST::PathSegment> path_segment
%type <P<AST::Binary>> binary
%type <P<AST::Pat>> pat
%type <P<AST::Ty>> type
%type <P<AST::Ty>> local_type
%type <P<AST::Call>> call
%type <P<AST::Loop>> loop_expr
%type <P<AST::If>> if_expr
%type <P<AST::Expr>> else_expr
%type <P<AST::While>> while_expr
%type <AST::Break> break
%type <Vec<P<AST::Expr>>> exprs
%type <bool> bool
%type <P<AST::Assign>> assign
%type <P<AST::Assign>> op_assign
%type <P<AST::Unary>> unary
%type <P<AST::Print>> print
%type <P<AST::Mod>> module
%type <std::string> str
%type <AST::Unit> unit
%type <AST::Str> str_ty

// custom
%token PRINT
%token STR

%%
// productions
crate:
    items END {
        driver.ast = Opt<P<AST::Crate>>(driver.rules->crate(std::move($1)));
        $$ = 1;
    }
    ;

items:
    items item { $$ = driver.rules->addItem(std::move($1), std::move($2)); }
    | { $$ = driver.rules->initItems(); }
    ;


item:
    function_definition { $$ = driver.rules->item(std::move($1)); }
    | module { $$ = driver.rules->item(std::move($1)); }
    ;

module:
    KW_MOD ident L_BRACE items R_BRACE { $$ = driver.rules->module(std::move($2), std::move($4)); }
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
    pat COLON type { $$ = driver.rules->param(std::move($1), std::move($3), false); }
    | KW_MUT pat COLON type { $$ = driver.rules->param(std::move($2), std::move($4), true); }
    ;

type:
    path { $$ = driver.rules->ty(std::move($1)); }
    | unit { $$ = driver.rules->ty(std::move($1)); }
    | str_ty { $$ = driver.rules->ty(std::move($1)); }
    ;

unit:
    L_PAREN R_PAREN { $$ = AST::Unit {}; }
    ;

str_ty:
    AND STR { $$ = AST::Str {}; }
    ;

block:
    L_BRACE statements R_BRACE { $$ = std::move($2); }
    ;

statements:
    statements_without_expr { $$ = std::move($1); }
    | statements_without_expr expr_without_block { $$ = driver.rules->addStatement(std::move($1), driver.rules->statement(std::move($2))); }
    ;

statements_without_expr:
    { $$ = driver.rules->initStatements(); }
    | statements_without_expr statement { $$ = driver.rules->addStatement(std::move($1), std::move($2)); }
    ;

statement:
    let { $$ = driver.rules->statement(std::move($1)); }
    | item { $$ = driver.rules->statement(std::move($1)); }
    | expr_without_block SEMI { $$ = driver.rules->statement(driver.rules->semi(std::move($1))); }
    | expr_with_block SEMI { $$ = driver.rules->statement(driver.rules->semi(std::move($1))); }
    // | expr_with_block  { $$ = driver.rules->statement(std::move($1)); }
    ;

ret:
    KW_RETURN expr { $$ = driver.rules->ret(std::move($2)); }
    | KW_RETURN { $$ = driver.rules->ret(); }
    ;

binary:
    expr PLUS expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Add{}, std::move($3)); }
    | expr MIN expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Sub{}, std::move($3)); }
    | expr STAR expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Mul{}, std::move($3)); }
    | expr SLASH expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Div{}, std::move($3)); }
    | expr PERCENT expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Mod{}, std::move($3)); }
    | expr AND_AND expr { $$ = driver.rules->binary(std::move($1), AST::Bin::And{}, std::move($3)); }
    | expr OR_OR expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Or{}, std::move($3)); }
    | expr EQ_EQ expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Eq{}, std::move($3)); }
    | expr NE expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Ne{}, std::move($3)); }
    | expr LT expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Lt{}, std::move($3)); }
    | expr LE expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Le{}, std::move($3)); }
    | expr GT expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Gt{}, std::move($3)); }
    | expr GE expr { $$ = driver.rules->binary(std::move($1), AST::Bin::Ge{}, std::move($3)); }
    ;

unary:
    MIN expr %prec U_MIN { $$ = driver.rules->unary(AST::Un::Neg{}, std::move($2)); }
    | PLUS expr %prec U_PLUS { $$ = driver.rules->unary(AST::Un::Pos{}, std::move($2)); }
    | NOT expr %prec U_NOT { $$ = driver.rules->unary(AST::Un::Not{}, std::move($2)); }
    ;

let:
    KW_LET pat local_type local_kind SEMI { $$ = driver.rules->let(std::move($2), std::move($3), std::move($4), false); }
    | KW_LET KW_MUT pat local_type local_kind SEMI { $$ = driver.rules->let(std::move($3), std::move($4), std::move($5), true); }
    ;

local_kind:
    EQ expr { $$ = std::move($2); }
    | { $$ = AST::Decl {}; }
    ;

local_type:
    COLON type { $$ = std::move($2); }
    | { $$ = driver.rules->ty(AST::TyKind(AST::Infer {})); }

exprs:
    exprs COMMA expr { $$ = driver.rules->addExpr(std::move($1), std::move($3)); }
    | expr { $$ = driver.rules->initExprs(std::move($1)); }
    | { $$ = driver.rules->initExprs(); }
    ;

expr:
    expr_without_block { $$ = std::move($1); }
    | expr_with_block { $$ = std::move($1); }
    ;

expr_without_block:
    expr_without_block_raw { $$ = std::move($1); }
    | L_PAREN expr_without_block_raw R_PAREN { $$ = std::move($2); }
    | L_PAREN expr_with_block R_PAREN { $$ = std::move($2); }
    ;

expr_without_block_raw:
    op_assign { $$ = driver.rules->expr(std::move($1)); }
    | binary { $$ = driver.rules->expr(std::move($1)); }
    | unary { $$ = driver.rules->expr(std::move($1)); }
    | literal { $$ = driver.rules->expr(std::move($1)); }
    | path { $$ = driver.rules->expr(std::move($1)); }
    | call { $$ = driver.rules->expr(std::move($1)); }
    | ret { $$ = driver.rules->expr(std::move($1)); }
    | break { $$ = driver.rules->expr(std::move($1)); }
    | assign { $$ = driver.rules->expr(std::move($1)); }
    | print { $$ = driver.rules->expr(std::move($1)); }
    ;

expr_with_block:
    block { $$ = driver.rules->expr(std::move($1)); }
    | if_expr { $$ = driver.rules->expr(std::move($1)); }
    | while_expr { $$ = driver.rules->expr(std::move($1)); }
    | loop_expr { $$ = driver.rules->expr(std::move($1)); }
    ;

op_assign:
    ident PLUS_EQ expr { $$ = driver.rules->opAssign(std::move($1), AST::Bin::Add{}, std::move($3)); }
    | ident MINUS_EQ expr { $$ = driver.rules->opAssign(std::move($1), AST::Bin::Sub{}, std::move($3)); }
    | ident STAR_EQ expr { $$ = driver.rules->opAssign(std::move($1), AST::Bin::Mul{}, std::move($3)); }
    | ident SLASH_EQ expr { $$ = driver.rules->opAssign(std::move($1), AST::Bin::Div{}, std::move($3)); }
    | ident PERCENT_EQ expr { $$ = driver.rules->opAssign(std::move($1), AST::Bin::Mod{}, std::move($3)); }
    ;


assign:
    ident EQ expr { $$ = driver.rules->assign(std::move($1), std::move($3)); }
    ;

break:
    KW_BREAK { $$ = driver.rules->breakExpr(); }
    ;

if_expr:
    KW_IF expr block { $$ = driver.rules->ifExpr(std::move($2), std::move($3), std::nullopt); }
    | KW_IF expr block else_expr { $$ = driver.rules->ifExpr(std::move($2), std::move($3), std::optional<P<AST::Expr>>{std::move($4)}); }
    ;

else_expr:
    KW_ELSE block { $$ = driver.rules->expr(std::move($2)); }
    | KW_ELSE if_expr { $$ = driver.rules->expr(std::move($2)); }
    ;

while_expr:
    KW_WHILE expr block { $$ = driver.rules->whileExpr(std::move($2), std::move($3)); }
    ;

loop_expr:
    KW_LOOP block { $$ = driver.rules->loopExpr(std::move($2)); }
    ;

call:
    path L_PAREN exprs R_PAREN { $$ = driver.rules->call(std::move($1), std::move($3)); }
    ;

pat:
    ident { $$ = driver.rules->pat(std::move($1)); }
    ;

ident:
    IDENTIFIER { $$ = driver.rules->ident($1); }
    ;

path:
    path_segment { $$ = driver.rules->initPath(std::move($1)); }
    | path PATH_SEP path_segment { $$ = driver.rules->addPathSegment(std::move($1), std::move($3)); }
    ;

path_segment:
    ident { $$ = driver.rules->pathSegment(std::move($1)); }
    | KW_SUPER { $$ = driver.rules->pathSegment(driver.rules->ident("super")); }
    ;

literal:
    INTEGER_LITERAL { $$ = driver.rules->lit($1); }
    | FLOAT_LITERAL { $$ = driver.rules->lit($1); }
    | str { $$ = driver.rules->lit($1); }
    | bool { $$ = driver.rules->lit($1); }
    | L_PAREN R_PAREN { $$ = driver.rules->lit(std::monostate{}); }
    ;

bool:
    KW_TRUE { $$ = true; }
    | KW_FALSE { $$ = false; }
    ;

str:
    STRING_LITERAL { $$ = driver.rules->str($1); }
    ;

print:
    PRINT L_PAREN str R_PAREN { $$ = driver.rules->print(std::move($3)); }

%%

void MRI::Parser::error(const location &loc , const std::string &message) {
	std::cout << "Error"
        << "(" << loc << "): "
        << message << std::endl;
}
