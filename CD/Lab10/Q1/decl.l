%{
#include "decl.tab.h"
%}

%%

int      { return INT; }
char     { return CHAR; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
","      { return ','; }
";"      { return ';'; }
[ \t\n]+ { /* ignore whitespace */ }

.        { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
