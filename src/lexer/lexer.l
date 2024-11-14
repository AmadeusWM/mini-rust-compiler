%{
#include "scanner.h"

using namespace MRI;

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

as       { return MRI::Parser::make_KW_AS(MRI::location()); }
break    { return MRI::Parser::make_KW_BREAK(MRI::location()); }
const    { return MRI::Parser::make_KW_CONST(MRI::location()); }
continue { return MRI::Parser::make_KW_CONTINUE(MRI::location()); }
crate    { return MRI::Parser::make_KW_CRATE(MRI::location()); }
else     { return MRI::Parser::make_KW_ELSE(MRI::location()); }
enum     { return MRI::Parser::make_KW_ENUM(MRI::location()); }
extern   { return MRI::Parser::make_KW_EXTERN(MRI::location()); }
{FALSE}  { return MRI::Parser::make_KW_FALSE(MRI::location()); }
fn       { return MRI::Parser::make_KW_FN(MRI::location()); }
for      { return MRI::Parser::make_KW_FOR(MRI::location()); }
if       { return MRI::Parser::make_KW_IF(MRI::location()); }
impl     { return MRI::Parser::make_KW_IMPL(MRI::location()); }
in       { return MRI::Parser::make_KW_IN(MRI::location()); }
let      { return MRI::Parser::make_KW_LET(MRI::location()); }
loop     { return MRI::Parser::make_KW_LOOP(MRI::location()); }
match    { return MRI::Parser::make_KW_MATCH(MRI::location()); }
mod      { return MRI::Parser::make_KW_MOD(MRI::location()); }
move     { return MRI::Parser::make_KW_MOVE(MRI::location()); }
mut      { return MRI::Parser::make_KW_MUT(MRI::location()); }
pub      { return MRI::Parser::make_KW_PUB(MRI::location()); }
ref      { return MRI::Parser::make_KW_REF(MRI::location()); }
return   { return MRI::Parser::make_KW_RETURN(MRI::location()); }
self     { return MRI::Parser::make_KW_SELFVALUE(MRI::location()); }
Self     { return MRI::Parser::make_KW_SELFTYPE(MRI::location()); }
static   { return MRI::Parser::make_KW_STATIC(MRI::location()); }
struct   { return MRI::Parser::make_KW_STRUCT(MRI::location()); }
super    { return MRI::Parser::make_KW_SUPER(MRI::location()); }
trait    { return MRI::Parser::make_KW_TRAIT(MRI::location()); }
{TRUE}   { return MRI::Parser::make_KW_TRUE(MRI::location()); }
type     { return MRI::Parser::make_KW_TYPE(MRI::location()); }
unsafe   { return MRI::Parser::make_KW_UNSAFE(MRI::location()); }
use      { return MRI::Parser::make_KW_USE(MRI::location()); }
where    { return MRI::Parser::make_KW_WHERE(MRI::location()); }
while    { return MRI::Parser::make_KW_WHILE(MRI::location()); }
async    { return MRI::Parser::make_KW_ASYNC(MRI::location()); }
await    { return MRI::Parser::make_KW_AWAIT(MRI::location()); }
dyn      { return MRI::Parser::make_KW_DYN(MRI::location()); }
abstract { return MRI::Parser::make_KW_ABSTRACT(MRI::location()); }
become   { return MRI::Parser::make_KW_BECOME(MRI::location()); }
box      { return MRI::Parser::make_KW_BOX(MRI::location()); }
do       { return MRI::Parser::make_KW_DO(MRI::location()); }
final    { return MRI::Parser::make_KW_FINAL(MRI::location()); }
macro    { return MRI::Parser::make_KW_MACRO(MRI::location()); }
override { return MRI::Parser::make_KW_OVERRIDE(MRI::location()); }
priv     { return MRI::Parser::make_KW_PRIV(MRI::location()); }
typeof   { return MRI::Parser::make_KW_TYPEOF(MRI::location()); }
unsized  { return MRI::Parser::make_KW_UNSIZED(MRI::location()); }
virtual  { return MRI::Parser::make_KW_VIRTUAL(MRI::location()); }
yield    { return MRI::Parser::make_KW_YIELD(MRI::location()); }
try      { return MRI::Parser::make_KW_TRY(MRI::location()); }

"+"        { return MRI::Parser::make_PLUS(MRI::location()); }
"-"        { return MRI::Parser::make_MIN(MRI::location()); }
"*"        { return MRI::Parser::make_STAR(MRI::location()); }
"/"        { return MRI::Parser::make_SLASH(MRI::location()); }
"%"        { return MRI::Parser::make_PERCENT(MRI::location()); }
"^"        { return MRI::Parser::make_CARET(MRI::location()); }
"!"        { return MRI::Parser::make_NOT(MRI::location()); }
"&"        { return MRI::Parser::make_AND(MRI::location()); }
"|"        { return MRI::Parser::make_OR(MRI::location()); }
"&&"       { return MRI::Parser::make_AND_AND(MRI::location()); }
"||"       { return MRI::Parser::make_OR_OR(MRI::location()); }
"<<"       { return MRI::Parser::make_SHL(MRI::location()); }
">>"       { return MRI::Parser::make_SHR(MRI::location()); }
"+="       { return MRI::Parser::make_PLUS_EQ(MRI::location()); }
"-="       { return MRI::Parser::make_MINUS_EQ(MRI::location()); }
"*="       { return MRI::Parser::make_STAR_EQ(MRI::location()); }
"/="       { return MRI::Parser::make_SLASH_EQ(MRI::location()); }
"%="       { return MRI::Parser::make_PERCENT_EQ(MRI::location()); }
"^="       { return MRI::Parser::make_CARET_EQ(MRI::location()); }
"&="       { return MRI::Parser::make_AND_EQ(MRI::location()); }
"|="       { return MRI::Parser::make_OR_EQ(MRI::location()); }
"<<="      { return MRI::Parser::make_SHL_EQ(MRI::location()); }
">>="      { return MRI::Parser::make_SHR_EQ(MRI::location()); }
"="        { return MRI::Parser::make_EQ(MRI::location()); }
"=="       { return MRI::Parser::make_EQ_EQ(MRI::location()); }
"!="       { return MRI::Parser::make_NE(MRI::location()); }
">"        { return MRI::Parser::make_GT(MRI::location()); }
"<"        { return MRI::Parser::make_LT(MRI::location()); }
">="       { return MRI::Parser::make_GE(MRI::location()); }
"<="       { return MRI::Parser::make_LE(MRI::location()); }
"@"        { return MRI::Parser::make_AT(MRI::location()); }
"_"        { return MRI::Parser::make_UNDERSCORE(MRI::location()); }
"."        { return MRI::Parser::make_DOT(MRI::location()); }
".."       { return MRI::Parser::make_DOT_DOT(MRI::location()); }
"..."      { return MRI::Parser::make_DOT_DOT_DOT(MRI::location()); }
"..="      { return MRI::Parser::make_DOT_DOT_EQ(MRI::location()); }
","        { return MRI::Parser::make_COMMA(MRI::location()); }
";"        { return MRI::Parser::make_SEMI(MRI::location()); }
":"        { return MRI::Parser::make_COLON(MRI::location()); }
"::"       { return MRI::Parser::make_PATH_SEP(MRI::location()); }
"->"       { return MRI::Parser::make_R_ARROW(MRI::location()); }
"=>"       { return MRI::Parser::make_FAT_ARROW(MRI::location()); }
"<-"       { return MRI::Parser::make_L_ARROW(MRI::location()); }
"#"        { return MRI::Parser::make_POUND(MRI::location()); }
"$"        { return MRI::Parser::make_DOLLAR(MRI::location()); }
"?"        { return MRI::Parser::make_QUESTION(MRI::location()); }
"~"        { return MRI::Parser::make_TILDE(MRI::location()); }

"("        { return MRI::Parser::make_L_PAREN(MRI::location()); }
")"        { return MRI::Parser::make_R_PAREN(MRI::location()); }
"{"        { return MRI::Parser::make_L_BRACE(MRI::location()); }
"}"        { return MRI::Parser::make_R_BRACE(MRI::location()); }
"["        { return MRI::Parser::make_L_BRACKET(MRI::location()); }
"]"        { return MRI::Parser::make_R_BRACKET(MRI::location()); }

{identifier}       { return MRI::Parser::make_IDENTIFIER(MRI::location()); }
{digit}*           { return MRI::Parser::make_INTEGER_LITERAL(MRI::location()); }
\"(\\.|[^"\\])*\"  { return MRI::Parser::make_STRING_LITERAL(MRI::location()); }

println!              { return MRI::Parser::make_PRINT(MRI::location()); }


<<EOF>>   { return MRI::Parser::make_END(MRI::location()); }

. {}

%%
