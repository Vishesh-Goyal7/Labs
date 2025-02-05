%{
#include <stdio.h>
int vowel_count = 0;
int consonant_count = 0;
%}

%%

[aAeEiIoOuU]       { vowel_count++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] { consonant_count++; }
.|\n                { /* Ignore other characters */ }

%%

int main() {
    yylex();  // Start scanning the input
    printf("Vowels: %d\n", vowel_count);
    printf("Consonants: %d\n", consonant_count);
    return 0;
}
