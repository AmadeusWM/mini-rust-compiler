int num_lines = 0, num_chars = 0;
%{
#define A 1
%}
%%
\n ++num_lines; ++num_chars;
.  ++num_chars;
if { return A; }
%%
main() {
	yylex();
	printf("# of lines = %d, # of chars = %d\n", num_lines, num_chars);
}
