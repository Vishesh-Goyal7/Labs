%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token INT CHAR ID

%%

declaration : data_type identifier_list ';'  { printf("Valid declaration\n"); }
            ;

data_type   : INT
            | CHAR
            ;

identifier_list : ID
                | ID ',' identifier_list
                ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main() {
    printf("Enter a declaration statement:\n");
    return yyparse();
}
