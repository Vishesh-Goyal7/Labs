%{
#include <stdio.h>

int pos_int = 0, neg_int = 0, pos_float = 0, neg_float = 0;
%}

%%
[-]?[0-9]+\.[0-9]+   { 
    if (yytext[0] == '-') neg_float++; 
    else pos_float++; 
} 

[-]?[0-9]+           { 
    if (yytext[0] == '-') neg_int++; 
    else pos_int++; 
} 

.   ; // Ignore other characters
%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }
    yyin = file;

    yylex(); // Call lexer

    printf("Positive Integers: %d\n", pos_int);
    printf("Negative Integers: %d\n", neg_int);
    printf("Positive Floats: %d\n", pos_float);
    printf("Negative Floats: %d\n", neg_float);

    fclose(file);
    return 0;
}

int yywrap() {
    return 1;
}
