%{
#include "scanner.h"
#include <iostream>
%}

%option c++
%option yyclass="Scanner"
%option nodefault noyywrap

digit      [0-9]
identifier ([a-z]|[A-Z]|\_)([a-z]|[A-Z]|[0-9]|\_)*
FALSE      false
TRUE       true

%%

%{
    using Token = MRI::Parser;

    int yycolumn = 1;

    #define YY_USER_ACTION yylloc.step(); yylloc.columns(yyleng);
%}

as       { return Token::make_KW_AS(yylloc); }
break    { return Token::make_KW_BREAK(yylloc); }
const    { return Token::make_KW_CONST(yylloc); }
continue { return Token::make_KW_CONTINUE(yylloc); }
crate    { return Token::make_KW_CRATE(yylloc); }
else     { return Token::make_KW_ELSE(yylloc); }
enum     { return Token::make_KW_ENUM(yylloc); }
extern   { return Token::make_KW_EXTERN(yylloc); }
fn       { return Token::make_KW_FN(yylloc); }
for      { return Token::make_KW_FOR(yylloc); }
if       { return Token::make_KW_IF(yylloc); }
impl     { return Token::make_KW_IMPL(yylloc); }
in       { return Token::make_KW_IN(yylloc); }
let      { return Token::make_KW_LET(yylloc); }
loop     { return Token::make_KW_LOOP(yylloc); }
match    { return Token::make_KW_MATCH(yylloc); }
mod      { return Token::make_KW_MOD(yylloc); }
move     { return Token::make_KW_MOVE(yylloc); }
mut      { return Token::make_KW_MUT(yylloc); }
pub      { return Token::make_KW_PUB(yylloc); }
ref      { return Token::make_KW_REF(yylloc); }
return   { return Token::make_KW_RETURN(yylloc); }
self     { return Token::make_KW_SELFVALUE(yylloc); }
Self     { return Token::make_KW_SELFTYPE(yylloc); }
static   { return Token::make_KW_STATIC(yylloc); }
struct   { return Token::make_KW_STRUCT(yylloc); }
super    { return Token::make_KW_SUPER(yylloc); }
trait    { return Token::make_KW_TRAIT(yylloc); }
{TRUE}   { return Token::make_KW_TRUE(yylloc); }
{FALSE}  { return Token::make_KW_FALSE(yylloc); }
type     { return Token::make_KW_TYPE(yylloc); }
unsafe   { return Token::make_KW_UNSAFE(yylloc); }
use      { return Token::make_KW_USE(yylloc); }
where    { return Token::make_KW_WHERE(yylloc); }
while    { return Token::make_KW_WHILE(yylloc); }
async    { return Token::make_KW_ASYNC(yylloc); }
await    { return Token::make_KW_AWAIT(yylloc); }
dyn      { return Token::make_KW_DYN(yylloc); }
abstract { return Token::make_KW_ABSTRACT(yylloc); }
become   { return Token::make_KW_BECOME(yylloc); }
box      { return Token::make_KW_BOX(yylloc); }
do       { return Token::make_KW_DO(yylloc); }
final    { return Token::make_KW_FINAL(yylloc); }
macro    { return Token::make_KW_MACRO(yylloc); }
override { return Token::make_KW_OVERRIDE(yylloc); }
priv     { return Token::make_KW_PRIV(yylloc); }
typeof   { return Token::make_KW_TYPEOF(yylloc); }
unsized  { return Token::make_KW_UNSIZED(yylloc); }
virtual  { return Token::make_KW_VIRTUAL(yylloc); }
yield    { return Token::make_KW_YIELD(yylloc); }
try      { return Token::make_KW_TRY(yylloc); }

"+"        { return Token::make_PLUS(yylloc); }
"-"        { return Token::make_MIN(yylloc); }
"*"        { return Token::make_STAR(yylloc); }
"/"        { return Token::make_SLASH(yylloc); }
"%"        { return Token::make_PERCENT(yylloc); }
"^"        { return Token::make_CARET(yylloc); }
"!"        { return Token::make_NOT(yylloc); }
"&"        { return Token::make_AND(yylloc); }
"|"        { return Token::make_OR(yylloc); }
"&&"       { return Token::make_AND_AND(yylloc); }
"||"       { return Token::make_OR_OR(yylloc); }
"<<"       { return Token::make_SHL(yylloc); }
">>"       { return Token::make_SHR(yylloc); }
"+="       { return Token::make_PLUS_EQ(yylloc); }
"-="       { return Token::make_MINUS_EQ(yylloc); }
"*="       { return Token::make_STAR_EQ(yylloc); }
"/="       { return Token::make_SLASH_EQ(yylloc); }
"%="       { return Token::make_PERCENT_EQ(yylloc); }
"^="       { return Token::make_CARET_EQ(yylloc); }
"&="       { return Token::make_AND_EQ(yylloc); }
"|="       { return Token::make_OR_EQ(yylloc); }
"<<="      { return Token::make_SHL_EQ(yylloc); }
">>="      { return Token::make_SHR_EQ(yylloc); }
"="        { return Token::make_EQ(yylloc); }
"=="       { return Token::make_EQ_EQ(yylloc); }
"!="       { return Token::make_NE(yylloc); }
">"        { return Token::make_GT(yylloc); }
"<"        { return Token::make_LT(yylloc); }
">="       { return Token::make_GE(yylloc); }
"<="       { return Token::make_LE(yylloc); }
"@"        { return Token::make_AT(yylloc); }
"_"        { return Token::make_UNDERSCORE(yylloc); }
"."        { return Token::make_DOT(yylloc); }
".."       { return Token::make_DOT_DOT(yylloc); }
"..."      { return Token::make_DOT_DOT_DOT(yylloc); }
"..="      { return Token::make_DOT_DOT_EQ(yylloc); }
","        { return Token::make_COMMA(yylloc); }
";"        { return Token::make_SEMI(yylloc); }
":"        { return Token::make_COLON(yylloc); }
"::"       { return Token::make_PATH_SEP(yylloc); }
"->"       { return Token::make_R_ARROW(yylloc); }
"=>"       { return Token::make_FAT_ARROW(yylloc); }
"<-"       { return Token::make_L_ARROW(yylloc); }
"#"        { return Token::make_POUND(yylloc); }
"$"        { return Token::make_DOLLAR(yylloc); }
"?"        { return Token::make_QUESTION(yylloc); }
"~"        { return Token::make_TILDE(yylloc); }

"("        { return Token::make_L_PAREN(yylloc); }
")"        { return Token::make_R_PAREN(yylloc); }
"{"        { return Token::make_L_BRACE(yylloc); }
"}"        { return Token::make_R_BRACE(yylloc); }
"["        { return Token::make_L_BRACKET(yylloc); }
"]"        { return Token::make_R_BRACKET(yylloc); }


{identifier}       { return Token::make_IDENTIFIER(yytext, yylloc); }
{digit}*           { return Token::make_INTEGER_LITERAL(atoi(yytext), yylloc); }
\"(\\.|[^"\\])*\"  { return Token::make_STRING_LITERAL(yytext, yylloc); }

"println!"         { return Token::make_PRINT(yylloc); }


<<EOF>>   { return Token::make_END(yylloc); }

.   {}
\n  {
    // move to the next line
    yylloc.lines(1);
}

%%
