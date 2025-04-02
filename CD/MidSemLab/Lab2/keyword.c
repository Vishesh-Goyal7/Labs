#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 32

const char *keywords[MAX_KEYWORDS] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int is_keyword(const char *word) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *file, *outputFile;
    char filename[100], outputFilename[100] = "output.txt";
    char line[1024], word[100];
    
    printf("Enter the filename: ");
    scanf("%s", filename);
    
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }
    
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Could not create file %s\n", outputFilename);
        fclose(file);
        return 1;
    }
    
    while (fgets(line, sizeof(line), file) != NULL) {
        char *ptr = line;
        while (*ptr) {
            if (isalpha(*ptr)) { 
                int i = 0;
                while (isalnum(*ptr) || *ptr == '_') {
                    word[i++] = *ptr++;
                }
                word[i] = '\0';
                if (is_keyword(word)) {
                    to_uppercase(word);
                }
                fputs(word, outputFile);
            } else {
                fputc(*ptr, outputFile);
                ptr++;
            }
        }
    }
    
    fclose(file);
    fclose(outputFile);
    
    printf("Processed file saved as %s\n", outputFilename);
    return 0;
}