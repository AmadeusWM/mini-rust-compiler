%{
#include "scanner.h"
#include <iostream>
// #define YY_USER_ACTION std::cout << "Token: " << yylloc << std::endl;
// #define YY_USER_ACTION  yylloc.columns(yyleng);
static void yyIncrease(int len);
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
    
    int yycolumn = 1;

    #define yylloc.step(); yylloc.columns(yyleng);
%}

as       { return MRI::Parser::make_KW_AS(yylloc); }
break    { return MRI::Parser::make_KW_BREAK(yylloc); }
const    { return MRI::Parser::make_KW_CONST(yylloc); }
continue { return MRI::Parser::make_KW_CONTINUE(yylloc); }
crate    { return MRI::Parser::make_KW_CRATE(yylloc); }
else     { return MRI::Parser::make_KW_ELSE(yylloc); }
enum     { return MRI::Parser::make_KW_ENUM(yylloc); }
extern   { return MRI::Parser::make_KW_EXTERN(yylloc); }
{FALSE}  { return MRI::Parser::make_KW_FALSE(yylloc); }
fn       { return MRI::Parser::make_KW_FN(yylloc); }
for      { return MRI::Parser::make_KW_FOR(yylloc); }
if       { return MRI::Parser::make_KW_IF(yylloc); }
impl     { return MRI::Parser::make_KW_IMPL(yylloc); }
in       { return MRI::Parser::make_KW_IN(yylloc); }
let      { return MRI::Parser::make_KW_LET(yylloc); }
loop     { return MRI::Parser::make_KW_LOOP(yylloc); }
match    { return MRI::Parser::make_KW_MATCH(yylloc); }
mod      { return MRI::Parser::make_KW_MOD(yylloc); }
move     { return MRI::Parser::make_KW_MOVE(yylloc); }
mut      { return MRI::Parser::make_KW_MUT(yylloc); }
pub      { return MRI::Parser::make_KW_PUB(yylloc); }
ref      { return MRI::Parser::make_KW_REF(yylloc); }
return   { return MRI::Parser::make_KW_RETURN(yylloc); }
self     { return MRI::Parser::make_KW_SELFVALUE(yylloc); }
Self     { return MRI::Parser::make_KW_SELFTYPE(yylloc); }
static   { return MRI::Parser::make_KW_STATIC(yylloc); }
struct   { return MRI::Parser::make_KW_STRUCT(yylloc); }
super    { return MRI::Parser::make_KW_SUPER(yylloc); }
trait    { return MRI::Parser::make_KW_TRAIT(yylloc); }
{TRUE}   { return MRI::Parser::make_KW_TRUE(yylloc); }
type     { return MRI::Parser::make_KW_TYPE(yylloc); }
unsafe   { return MRI::Parser::make_KW_UNSAFE(yylloc); }
use      { return MRI::Parser::make_KW_USE(yylloc); }
where    { return MRI::Parser::make_KW_WHERE(yylloc); }
while    { return MRI::Parser::make_KW_WHILE(yylloc); }
async    { return MRI::Parser::make_KW_ASYNC(yylloc); }
await    { return MRI::Parser::make_KW_AWAIT(yylloc); }
dyn      { return MRI::Parser::make_KW_DYN(yylloc); }
abstract { return MRI::Parser::make_KW_ABSTRACT(yylloc); }
become   { return MRI::Parser::make_KW_BECOME(yylloc); }
box      { return MRI::Parser::make_KW_BOX(yylloc); }
do       { return MRI::Parser::make_KW_DO(yylloc); }
final    { return MRI::Parser::make_KW_FINAL(yylloc); }
macro    { return MRI::Parser::make_KW_MACRO(yylloc); }
override { return MRI::Parser::make_KW_OVERRIDE(yylloc); }
priv     { return MRI::Parser::make_KW_PRIV(yylloc); }
typeof   { return MRI::Parser::make_KW_TYPEOF(yylloc); }
unsized  { return MRI::Parser::make_KW_UNSIZED(yylloc); }
virtual  { return MRI::Parser::make_KW_VIRTUAL(yylloc); }
yield    { return MRI::Parser::make_KW_YIELD(yylloc); }
try      { return MRI::Parser::make_KW_TRY(yylloc); }

"+"        { return MRI::Parser::make_PLUS(yylloc); }
"-"        { return MRI::Parser::make_MIN(yylloc); }
"*"        { return MRI::Parser::make_STAR(yylloc); }
"/"        { return MRI::Parser::make_SLASH(yylloc); }
"%"        { return MRI::Parser::make_PERCENT(yylloc); }
"^"        { return MRI::Parser::make_CARET(yylloc); }
"!"        { return MRI::Parser::make_NOT(yylloc); }
"&"        { return MRI::Parser::make_AND(yylloc); }
"|"        { return MRI::Parser::make_OR(yylloc); }
"&&"       { return MRI::Parser::make_AND_AND(yylloc); }
"||"       { return MRI::Parser::make_OR_OR(yylloc); }
"<<"       { return MRI::Parser::make_SHL(yylloc); }
">>"       { return MRI::Parser::make_SHR(yylloc); }
"+="       { return MRI::Parser::make_PLUS_EQ(yylloc); }
"-="       { return MRI::Parser::make_MINUS_EQ(yylloc); }
"*="       { return MRI::Parser::make_STAR_EQ(yylloc); }
"/="       { return MRI::Parser::make_SLASH_EQ(yylloc); }
"%="       { return MRI::Parser::make_PERCENT_EQ(yylloc); }
"^="       { return MRI::Parser::make_CARET_EQ(yylloc); }
"&="       { return MRI::Parser::make_AND_EQ(yylloc); }
"|="       { return MRI::Parser::make_OR_EQ(yylloc); }
"<<="      { return MRI::Parser::make_SHL_EQ(yylloc); }
">>="      { return MRI::Parser::make_SHR_EQ(yylloc); }
"="        { return MRI::Parser::make_EQ(yylloc); }
"=="       { return MRI::Parser::make_EQ_EQ(yylloc); }
"!="       { return MRI::Parser::make_NE(yylloc); }
">"        { return MRI::Parser::make_GT(yylloc); }
"<"        { return MRI::Parser::make_LT(yylloc); }
">="       { return MRI::Parser::make_GE(yylloc); }
"<="       { return MRI::Parser::make_LE(yylloc); }
"@"        { return MRI::Parser::make_AT(yylloc); }
"_"        { return MRI::Parser::make_UNDERSCORE(yylloc); }
"."        { return MRI::Parser::make_DOT(yylloc); }
".."       { return MRI::Parser::make_DOT_DOT(yylloc); }
"..."      { return MRI::Parser::make_DOT_DOT_DOT(yylloc); }
"..="      { return MRI::Parser::make_DOT_DOT_EQ(yylloc); }
","        { return MRI::Parser::make_COMMA(yylloc); }
";"        { return MRI::Parser::make_SEMI(yylloc); }
":"        { return MRI::Parser::make_COLON(yylloc); }
"::"       { return MRI::Parser::make_PATH_SEP(yylloc); }
"->"       { return MRI::Parser::make_R_ARROW(yylloc); }
"=>"       { return MRI::Parser::make_FAT_ARROW(yylloc); }
"<-"       { return MRI::Parser::make_L_ARROW(yylloc); }
"#"        { return MRI::Parser::make_POUND(yylloc); }
"$"        { return MRI::Parser::make_DOLLAR(yylloc); }
"?"        { return MRI::Parser::make_QUESTION(yylloc); }
"~"        { return MRI::Parser::make_TILDE(yylloc); }

"("        { return MRI::Parser::make_L_PAREN(yylloc); }
")"        { return MRI::Parser::make_R_PAREN(yylloc); }
"{"        { return MRI::Parser::make_L_BRACE(yylloc); }
"}"        { return MRI::Parser::make_R_BRACE(yylloc); }
"["        { return MRI::Parser::make_L_BRACKET(yylloc); }
"]"        { return MRI::Parser::make_R_BRACKET(yylloc); }

{identifier}       { return MRI::Parser::make_IDENTIFIER(yytext, yylloc); }
{digit}*           { return MRI::Parser::make_INTEGER_LITERAL(yylloc); }
\"(\\.|[^"\\])*\"  { return MRI::Parser::make_STRING_LITERAL(yylloc); }

println!              { return MRI::Parser::make_PRINT(yylloc); }


<<EOF>>   { return MRI::Parser::make_END(yylloc); }

.|\n {}

%%
