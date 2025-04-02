#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 32
#define MAX_SYMBOLS 100

const char *keywords[MAX_KEYWORDS] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

typedef struct {
    char lexeme[100];
    int size;
    char type[20];
} Symbol;

typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

SymbolTable globalSymbolTable;

void initializeSymbolTable(SymbolTable *table) {
    table->count = 0;
}

void addSymbol(SymbolTable *table, const char *lexeme, const char *type, int size) {
    if (table->count < MAX_SYMBOLS) {
        strcpy(table->symbols[table->count].lexeme, lexeme);
        strcpy(table->symbols[table->count].type, type);
        table->symbols[table->count].size = size;
        table->count++;
    }
}

void printSymbolTable(SymbolTable *table, const char *name) {
    printf("\nSymbol Table: %s\n", name);
    printf("%-20s %-10s %-10s\n", "Lexeme", "Size", "Type");
    printf("--------------------------------------\n");
    for (int i = 0; i < table->count; i++) {
        printf("%-20s %-10d %-10s\n", table->symbols[i].lexeme, table->symbols[i].size, table->symbols[i].type);
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

void processFunction(FILE *file, SymbolTable *localTable) {
    char word[100];
    int ch;
    
    while ((ch = fgetc(file)) != EOF && ch != '}') {
        if (isalpha(ch) || ch == '_') {
            int i = 0;
            word[i++] = ch;
            while (isalnum(ch = fgetc(file)) || ch == '_') {
                word[i++] = ch;
            }
            word[i] = '\0';
            ungetc(ch, file);
            
            if (is_keyword(word)) {
                addSymbol(localTable, word, "KEYWORD", (int)strlen(word));
            } else {
                addSymbol(localTable, word, "IDENTIFIER", (int)strlen(word));
            }
        }
    }
}

void parseFile(FILE *file) {
    char word[100];
    int ch;
    SymbolTable localTable;
    
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch) || ch == '_') {
            int i = 0;
            word[i++] = ch;
            while (isalnum(ch = fgetc(file)) || ch == '_') {
                word[i++] = ch;
            }
            word[i] = '\0';
            ungetc(ch, file);
            
            if (is_keyword(word)) {
                addSymbol(&globalSymbolTable, word, "KEYWORD", (int)strlen(word));
            } else {
                ch = fgetc(file);
                if (ch == '(') {
                    initializeSymbolTable(&localTable);
                    addSymbol(&globalSymbolTable, word, "FUNCTION", (int)strlen(word));
                    processFunction(file, &localTable);
                    printSymbolTable(&localTable, word);
                } else {
                    ungetc(ch, file);
                    addSymbol(&globalSymbolTable, word, "IDENTIFIER", (int)strlen(word));
                }
            }
        }
    }
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
    
    initializeSymbolTable(&globalSymbolTable);
    parseFile(file);
    printSymbolTable(&globalSymbolTable, "Global Symbol Table");
    
    fclose(file);
    return 0;
}