#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NUM_KEYWORDS 32

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
    "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

int isKeyword(char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; 
        }
    }
    return 0;
}

void toUpperCase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = toupper(word[i]);
    }
}

void identifyKeywords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    char word[100];  

    printf("\nKeywords in uppercase:\n");

    while (fscanf(file, "%99s", word) == 1) {
        if (isKeyword(word)) {
            toUpperCase(word);  
            printf("%s ", word);    
        }
    }

    fclose(file);
    printf("\n");
}

int main() {
    char filename[100];

    printf("Enter the input C file: ");
    scanf("%s", filename);

    identifyKeywords(filename);

    return 0;
}
