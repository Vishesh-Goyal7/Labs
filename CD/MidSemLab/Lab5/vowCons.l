%{
#include <stdio.h>
int vowels = 0, consonants = 0;
%}

%%
[aeiouAEIOU] { vowels++; }
[a-zA-Z] { consonants++; }
.  ;   // Ignore other characters
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
    
    yylex(); // Call the lexer
    
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    
    fclose(file);
    return 0;
}

int yywrap() {
    return 1;
}