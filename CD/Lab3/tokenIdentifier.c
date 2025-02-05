#include "tokenIdentifier.h"
#include <ctype.h>
#include <string.h>

char *keywords[] = {"int", "float", "char", "if", "else", "for", "while", "return", "struct"};
int numKeywords = 8;

// Function to check if a word is a keyword
int isKeyword(char *word) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) return 1;
    }
    return 0;
}

// Function to get the next token from the file
Token getNextToken(FILE *file) {
    static int row = 1, col = 0;
    char ch;
    Token token;
    token.lexeme[0] = '\0';

    while ((ch = fgetc(file)) != EOF) {
        col++;

        if (ch == '\n') {
            row++;
            col = 0;
            continue;
        }

        if (ch == ' ' || ch == '\t') continue;

        if (isalpha(ch) || ch == '_') {  // Identifiers and Keywords
            int i = 0;
            token.lexeme[i++] = ch;
            while (isalnum(ch = fgetc(file)) || ch == '_') token.lexeme[i++] = ch;
            token.lexeme[i] = '\0';
            ungetc(ch, file);

            if (isKeyword(token.lexeme))
                strcpy(token.type, "KEYWORD");
            else
                strcpy(token.type, "IDENTIFIER");

            token.row = row;
            token.col = col;
            return token;
        }

        if (isdigit(ch)) {  // Numerical constants
            int i = 0;
            token.lexeme[i++] = ch;
            while (isdigit(ch = fgetc(file))) token.lexeme[i++] = ch;
            token.lexeme[i] = '\0';
            ungetc(ch, file);
            strcpy(token.type, "NUMERIC_CONSTANT");
            token.row = row;
            token.col = col;
            return token;
        }

        // Operators
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            strcpy(token.type, "ARITHMETIC_OPERATOR");
        } else if (ch == '=' || ch == '<' || ch == '>') {
            token.lexeme[0] = ch;
            ch = fgetc(file);
            if (ch == '=') {
                token.lexeme[1] = ch;
                token.lexeme[2] = '\0';
            } else {
                token.lexeme[1] = '\0';
                ungetc(ch, file);
            }
            strcpy(token.type, "RELATIONAL_OPERATOR");
        } else if (ch == '&' || ch == '|') {
            char next = fgetc(file);
            if ((ch == '&' && next == '&') || (ch == '|' && next == '|')) {
                token.lexeme[0] = ch;
                token.lexeme[1] = next;
                token.lexeme[2] = '\0';
                strcpy(token.type, "LOGICAL_OPERATOR");
            } else {
                ungetc(next, file);
                continue;
            }
        } else {
            continue;
        }

        token.row = row;
        token.col = col;
        return token;
    }

    strcpy(token.lexeme, "EOF");
    strcpy(token.type, "END_OF_FILE");
    return token;
}
