#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 32

const char *keywords[MAX_KEYWORDS] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

typedef struct {
    int row;
    int col;
    char type[20];
    char value[100];
} Token;

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

int is_operator(char ch) {
    return strchr("+-*/%<>=!&|^", ch) != NULL;
}

int is_special_symbol(char ch) {
    return strchr("{}[]();,.", ch) != NULL;
}

Token getNextToken(FILE *file, int *row, int *col) {
    Token token;
    token.row = *row;
    token.col = *col;
    int ch = fgetc(file);
    
    if (ch == EOF) {
        strcpy(token.type, "EOF");
        return token;
    }

    if (isspace(ch)) {
        if (ch == '\n') {
            (*row)++;
            *col = 1;
        } else {
            (*col)++;
        }
        return getNextToken(file, row, col);
    }

    if (isalpha(ch) || ch == '_') {
        int i = 0;
        char word[100];
        word[i++] = ch;
        while (isalnum(ch = fgetc(file)) || ch == '_') {
            word[i++] = ch;
        }
        word[i] = '\0';
        ungetc(ch, file);
        
        if (is_keyword(word)) {
            strcpy(token.type, "KEYWORD");
            to_uppercase(word);
        } else {
            strcpy(token.type, "IDENTIFIER");
        }
        strcpy(token.value, word);
        return token;
    }

    if (is_operator(ch)) {
        token.value[0] = ch;
        token.value[1] = '\0';
        strcpy(token.type, "OPERATOR");
        return token;
    }

    if (is_special_symbol(ch)) {
        token.value[0] = ch;
        token.value[1] = '\0';
        strcpy(token.type, "SPECIAL_SYMBOL");
        return token;
    }

    if (isdigit(ch)) {
        int i = 0;
        char number[100];
        number[i++] = ch;
        while (isdigit(ch = fgetc(file))) {
            number[i++] = ch;
        }
        number[i] = '\0';
        ungetc(ch, file);
        strcpy(token.type, "NUMERIC_CONSTANT");
        strcpy(token.value, number);
        return token;
    }
    
    if (ch == '"') {
        int i = 0;
        char string[100];
        string[i++] = ch;
        while ((ch = fgetc(file)) != '"' && ch != EOF) {
            string[i++] = ch;
        }
        string[i++] = '"';
        string[i] = '\0';
        strcpy(token.type, "STRING_LITERAL");
        strcpy(token.value, string);
        return token;
    }

    strcpy(token.type, "UNKNOWN");
    token.value[0] = ch;
    token.value[1] = '\0';
    return token;
}

int main() {
    FILE *file;
    char filename[100];
    
    printf("Enter the filename: ");
    scanf("%s", filename);    
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }
    
    int row = 1, col = 1;
    Token token;
    
    while (1) {
        token = getNextToken(file, &row, &col);
        if (strcmp(token.type, "EOF") == 0) break;
        printf("Row: %d, Col: %d, Type: %s, Value: %s\n", token.row, token.col, token.type, token.value);
    }    
    fclose(file);
    return 0;
}