%{
#include "../parser/parser.h"
//#include "includes.h"
#include <string>
#include <cstdio>
#include <memory>

int line_nr = 1;
int col_nr = 1;
extern "C" int yylex();
%}

digit      [0-9]
identifier ([a-z]|[A-Z]|\_)([a-z]|[A-Z]|[0-9]|\_)*
FALSE      false
TRUE       true

%%
as       { return KW_AS; }
break    { return KW_BREAK; }
const    { return KW_CONST; }
continue { return KW_CONTINUE; }
crate    { return KW_CRATE; }
else     { return KW_ELSE; }
enum     { return KW_ENUM; }
extern   { return KW_EXTERN; }
{FALSE}  { return KW_FALSE; }
fn       { return KW_FN; }
for      { return KW_FOR; }
if       { return KW_IF; }
impl     { return KW_IMPL; }
in       { return KW_IN; }
let      { return KW_LET; }
loop     { return KW_LOOP; }
match    { return KW_MATCH; }
mod      { return KW_MOD; }
move     { return KW_MOVE; }
mut      { return KW_MUT; }
pub      { return KW_PUB; }
ref      { return KW_REF; }
return   { return KW_RETURN; }
self     { return KW_SELFVALUE; }
Self     { return KW_SELFTYPE; }
static   { return KW_STATIC; }
struct   { return KW_STRUCT; }
super    { return KW_SUPER; }
trait    { return KW_TRAIT; }
{TRUE}   { return KW_TRUE; }
type     { return KW_TYPE; }
unsafe   { return KW_UNSAFE; }
use      { return KW_USE; }
where    { return KW_WHERE; }
while    { return KW_WHILE; }
async    { return KW_ASYNC; }
await    { return KW_AWAIT; }
dyn      { return KW_DYN; }
abstract { return KW_ABSTRACT; }
become   { return KW_BECOME; }
box      { return KW_BOX; }
do       { return KW_DO; }
final    { return KW_FINAL; }
macro    { return KW_MACRO; }
override { return KW_OVERRIDE; }
priv     { return KW_PRIV; }
typeof   { return KW_TYPEOF; }
unsized  { return KW_UNSIZED; }
virtual  { return KW_VIRTUAL; }
yield    { return KW_YIELD; }
try      { return KW_TRY; }

"+"        { return PLUS; }
"-"        { return MIN; }
"*"        { return STAR; }
"/"        { return SLASH; }
"%"        { return PERCENT; }
"^"        { return CARET; }
"!"        { return NOT; }
"&"        { return AND; }
"|"        { return OR; }
"&&"       { return AND_AND; }
"||"       { return OR_OR; }
"<<"       { return SHL; }
">>"       { return SHR; }
"+="       { return PLUS_EQ; }
"-="       { return MINUS_EQ; }
"*="       { return STAR_EQ; }
"/="       { return SLASH_EQ; }
"%="       { return PERCENT_EQ; }
"^="       { return CARET_EQ; }
"&="       { return AND_EQ; }
"|="       { return OR_EQ; }
"<<="      { return SHL_EQ; }
">>="      { return SHR_EQ; }
"="        { return EQ; }
"=="       { return EQ_EQ; }
"!="       { return NE; }
">"        { return GT; }
"<"        { return LT; }
">="       { return GE; }
"<="       { return LE; }
"@"        { return AT; }
"_"        { return UNDERSCORE; }
"."        { return DOT; }
".."       { return DOT_DOT; }
"..."      { return DOT_DOT_DOT; }
"..="      { return DOT_DOT_EQ; }
","        { return COMMA; }
";"        { return SEMI; }
":"        { return COLON; }
"::"       { return PATH_SEP; }
"->"       { return R_ARROW; }
"=>"       { return FAT_ARROW; }
"<-"       { return L_ARROW; }
"#"        { return POUND; }
"$"        { return DOLLAR; }
"?"        { return QUESTION; }
"~"        { return TILDE; }

"("        { return L_PAREN; }
")"        { return R_PAREN; }
"{"        { return L_BRACE; }
"}"        { return R_BRACE; }
"["        { return L_BRACKET; }
"]"        { return R_BRACKET; }

{identifier}       { yylval.string_literal = strdup(yytext); return IDENTIFIER; }
{digit}*           { yylval.integer = std::atoi(yytext); return INTEGER_LITERAL; }
\"(\\.|[^"\\])*\"  { yylval.string_literal = strdup(yytext); return STRING_LITERAL; }

println!              { return PRINT; }

\n line_nr++; col_nr = 1;
.  ++col_nr;

%%

/* Function called by (f)lex when EOF is read. If yywrap returns a
   true (non-zero) (f)lex will terminate and continue otherwise.*/
int yywrap(){
  printf("# of lines = %d, # of chars = %d\n", line_nr, col_nr);
  return (1);
}
