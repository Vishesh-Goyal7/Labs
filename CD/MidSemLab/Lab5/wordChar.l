%{
#include <stdio.h>

int word_count = 0, char_count = 0, blank_count = 0, line_count = 0;
%}

%%
// Matching patterns
[ \t]+        { blank_count += yyleng; }  // Count blanks and tabs
\n            { line_count++; }           // Count lines
[A-Za-z0-9]+  { word_count++; }           // Count words
.             { char_count++; }           // Count other characters
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

    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Blanks: %d\n", blank_count);
    printf("Lines: %d\n", line_count);

    fclose(file);
    return 0;
}

int yywrap() {
    return 1;
}
