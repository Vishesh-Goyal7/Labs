#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Lab3/tokenIdentifier.h"

#define MAX_SYMBOLS 100

typedef struct {
    int serial;
    char name[100];
    char type[50];
    int size;
} Symbol;

Symbol globalTable[MAX_SYMBOLS];
Symbol localTable[MAX_SYMBOLS];
int globalCount = 0, localCount = 0;
int insideMain = 0;
char currentType[50] = ""; // Store current data type

// Function to add a symbol to the table
void addToSymbolTable(Symbol table[], int *count, Token token) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(table[i].name, token.lexeme) == 0) return;
    }

    Symbol newSymbol;
    newSymbol.serial = (*count) + 1;
    strcpy(newSymbol.name, token.lexeme);
    strcpy(newSymbol.type, currentType);

    if (strcmp(currentType, "int") == 0) newSymbol.size = 4;
    else if (strcmp(currentType, "float") == 0) newSymbol.size = 4;
    else if (strcmp(currentType, "char") == 0) newSymbol.size = 1;
    else newSymbol.size = 0;

    table[(*count)++] = newSymbol;
}

// Function to display a symbol table
void displaySymbolTable(Symbol table[], int count, const char *name) {
    printf("\n%s Symbol Table:\n", name);
    printf("------------------------------------------------\n");
    printf("| S.No. | Name        | Type        | Size (bytes) |\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("| %5d | %-10s | %-10s | %10d |\n",
               table[i].serial, table[i].name, table[i].type, table[i].size);
    }
    printf("------------------------------------------------\n");
}

int main() {

    char filename[100];

    printf("Enter the input C file: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    Token token;
    while (strcmp((token = getNextToken(file)).lexeme, "EOF") != 0) {
        if (strcmp(token.lexeme, "main") == 0) {
            insideMain = 1;
        }
        if (insideMain && strcmp(token.lexeme, "{") == 0) continue;
        if (insideMain && strcmp(token.lexeme, "}") == 0) {
            insideMain = 0;
            continue;
        }

        if (strcmp(token.type, "KEYWORD") == 0) {
            strcpy(currentType, token.lexeme);
        } else if (strcmp(token.type, "IDENTIFIER") == 0) {
            if (insideMain) {
                addToSymbolTable(localTable, &localCount, token);
            } else {
                addToSymbolTable(globalTable, &globalCount, token);
            }
        }
    }

    fclose(file);

    displaySymbolTable(globalTable, globalCount, "Global");
    displaySymbolTable(localTable, localCount, "Local");

    return 0;
}
