%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token IF ELSE WHILE ID RELOP

%%

program:
    statement { printf("✅ Valid statement\n"); }
    ;

statement:
      IF '(' condition ')' statement
    | IF '(' condition ')' statement ELSE statement
    | WHILE '(' condition ')' statement
    | compound_stmt
    | ID ';'
    ;

compound_stmt:
    '{' stmt_list '}'
    ;

stmt_list:
      statement
    | statement stmt_list
    ;

condition:
    ID RELOP ID
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "❌ Syntax Error: %s\n", s);
}

int main() {
    printf("Enter a decision-making or loop statement:\n");
    return yyparse();
}
