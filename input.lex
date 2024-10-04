int num_lines = 0, num_chars = 0;

%{
#define KW_AS 1
#define KW_BREAK 2
#define KW_CONST 3 
#define KW_CONTINUE 4 
#define KW_CRATE 5 
#define KW_ELSE 6 
#define KW_ENUM 7 
#define KW_EXTERN 8 
#define KW_FALSE 9 
#define KW_FN 10 
#define KW_FOR 11 
#define KW_IF 12 
#define KW_IMPL 13 
#define KW_IN 14 
#define KW_LET 15 
#define KW_LOOP 16 
#define KW_MATCH 17 
#define KW_MOD 18 
#define KW_MOVE 19 
#define KW_MUT 20 
#define KW_PUB 21 
#define KW_REF 22 
#define KW_RETURN 23 
#define KW_SELFVALUE 24 
#define KW_SELFTYPE 25 
#define KW_STATIC 26 
#define KW_STRUCT 27 
#define KW_SUPER 28 
#define KW_TRAIT 29 
#define KW_TRUE 30 
#define KW_TYPE 31 
#define KW_UNSAFE 32 
#define KW_USE 33 
#define KW_WHERE 34 
#define KW_WHILE 35 
#define KW_ASYNC 36 
#define KW_AWAIT 37 
#define KW_DYN 38 
#define KW_ABSTRACT 39 
#define KW_BECOME 40 
#define KW_BOX 41 
#define KW_DO 42 
#define KW_FINAL 43 
#define KW_MACRO 44 
#define KW_OVERRIDE 45 
#define KW_PRIV 46 
#define KW_TYPEOF 47 
#define KW_UNSIZED 48 
#define KW_VIRTUAL 49 
#define KW_YIELD 50 
#define KW_TRY 51 

#define PUNC_PLUS 52 
#define PUNC_MIN 53
#define PUNC_STAR 54
#define PUNC_SLASH 55
#define PUNC_PERCENT 56
#define PUNC_CARET 57
#define PUNC_NOT 58
#define PUNC_AND 59
#define PUNC_OR 60
#define PUNC_AND_AND 61
#define PUNC_OR_OR 62
#define PUNC_SHL 63
#define PUNC_SHR 64
#define PUNC_PLUS_EQ 65
#define PUNC_MINUS_EQ 66
#define PUNC_STAR_EQ 67
#define PUNC_SLASH_EQ 68
#define PUNC_PERCENT_EQ 69
#define PUNC_CARET_EQ 70
#define PUNC_AND_EQ 71
#define PUNC_OR_EQ 72
#define PUNC_SHL_EQ 73
#define PUNC_SHR_EQ 74
#define PUNC_EQ 75
#define PUNC_EQ_EQ 76
#define PUNC_NE 77
#define PUNC_GT 78
#define PUNC_LT 79
#define PUNC_GE 80
#define PUNC_LE 81
#define PUNC_AT 82
#define PUNC_UNDERSCORE 83
#define PUNC_DOT 84
#define PUNC_DOT_DOT 85
#define PUNC_DOT_DOT_DOT 86
#define PUNC_DOT_DOT_EQ 87
#define PUNC_COMMA 88
#define PUNC_SEMI 89
#define PUNC_COLON 90
#define PUNC_PATH_SEP 91
#define PUNC_R_ARROW 92
#define PUNC_FAT_ARROW 93
#define PUNC_L_ARROW 94
#define PUNC_POUND 95
#define PUNC_DOLALR 96
#define PUNC_QUESTION 97
#define PUNC_TILDE 98

#define L_PAREN 99
#define R_PAREN 100
#define L_BRACE 101
#define R_BRACE 102
#define L_BRACKET 103
#define R_BRACKET 104

#define IDENTIFIER 105

#define INTEGER_LITERAL 106

#define PRINTVAR 107
#define PRINTSTRING 108
%}

digit      [0-9]
identifier ([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])*
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

"+"        { return PUNC_PLUS; }
"-"        { return PUNC_MIN; }
"*"        { return PUNC_STAR; }
"/"        { return PUNC_SLASH; }
"%"        { return PUNC_PERCENT; }
"^"        { return PUNC_CARET; }
"!"        { return PUNC_NOT; }
"&"        { return PUNC_AND; }
"|"        { return PUNC_OR; }
"&&"       { return PUNC_AND_AND; }
"||"       { return PUNC_OR_OR; }
"<<"       { return PUNC_SHL; }
">>"       { return PUNC_SHR; }
"+="       { return PUNC_PLUS_EQ; }
"-="       { return PUNC_MINUS_EQ; }
"*="       { return PUNC_STAR_EQ; }
"/="       { return PUNC_SLASH_EQ; }
"%="       { return PUNC_PERCENT_EQ; }
"^="       { return PUNC_CARET_EQ; }
"&="       { return PUNC_AND_EQ; }
"|="       { return PUNC_OR_EQ; }
"<<="      { return PUNC_SHL_EQ; }
">>="      { return PUNC_SHR_EQ; }
"="        { return PUNC_EQ; }
"=="       { return PUNC_EQ_EQ; }
"!="       { return PUNC_NE; }
">"        { return PUNC_GT; }
"<"        { return PUNC_LT; }
">="       { return PUNC_GE; }
"<="       { return PUNC_LE; }
"@"        { return PUNC_AT; }
"_"        { return PUNC_UNDERSCORE; }
"."        { return PUNC_DOT; }
".."       { return PUNC_DOT_DOT; }
"..."      { return PUNC_DOT_DOT_DOT; }
"..="      { return PUNC_DOT_DOT_EQ; }
","        { return PUNC_COMMA; }
";"        { return PUNC_SEMI; }
":"        { return PUNC_COLON; }
"::"       { return PUNC_PATH_SEP; }
"->"       { return PUNC_R_ARROW; }
"=>"       { return PUNC_FAT_ARROW; }
"<-"       { return PUNC_L_ARROW; }
"#"        { return PUNC_POUND; }
"$"        { return PUNC_DOLALR; }
"?"        { return PUNC_QUESTION; }
"~"        { return PUNC_TILDE; }

"("        { return L_PAREN; }
")"        { return R_PAREN; }
"{"        { return L_BRACE; }
"}"        { return R_BRACE; }
"["        { return L_BRACKET; }
"]"        { return R_BRACKET; }

{identifier}       { return IDENTIFIER; }
{digit}*           { return INTEGER_LITERAL; }

println!\(\"\{[a-zA-Z0-9_]+\}\"\) { return PRINTVAR; }
println!\(\"[^\"]*\"\)            { return PRINTSTRING; }

\n ++num_lines; ++num_chars;
.  ++num_chars;

%%
main() {
	yylex();
	printf("# of lines = %d, # of chars = %d\n", num_lines, num_chars);
}
