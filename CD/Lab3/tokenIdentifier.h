#ifndef TOKEN_IDENTIFIER_H
#define TOKEN_IDENTIFIER_H

#include <stdio.h>

typedef struct {
    char lexeme[100];
    char type[50];
    int row, col;
} Token;

Token getNextToken(FILE *file);

#endif
