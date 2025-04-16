#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char tokens[MAX][MAX];
int row = 1, col = 1;
int pos = 0, totalTokens = 0;

void error(const char* expected) {
    printf("Syntax Error: Expected '%s' at row %d, column %d but found '%s'\n", expected, row, col, tokens[pos]);
    exit(1);
}

// --- Lexer: Breaks input into tokens and tracks line/column ---
void lexer(const char* code) {
    int i = 0, t = 0, k = 0;
    while (code[i]) {
        if (isspace(code[i])) {
            if (code[i] == '\n') {
                row++;
                col = 1;
            } else {
                col++;
            }
            i++;
            continue;
        }

        if (isalpha(code[i])) {
            k = 0;
            while (isalnum(code[i])) {
                tokens[t][k++] = code[i++];
                col++;
            }
            tokens[t++][k] = '\0';
        } else if (isdigit(code[i])) {
            k = 0;
            while (isdigit(code[i])) {
                tokens[t][k++] = code[i++];
                col++;
            }
            tokens[t++][k] = '\0';
        } else {
            tokens[t][0] = code[i++];
            tokens[t++][1] = '\0';
            col++;
        }
    }
    totalTokens = t;
    strcpy(tokens[t], "$"); // End of input marker
}

// --- Parser Functions ---

void match(const char* expected) {
    if (strcmp(tokens[pos], expected) == 0) {
        pos++;
    } else {
        error(expected);
    }
}

void assign_stat() {
    if (strcmp(tokens[pos + 1], "=") == 0 && (strcmp(tokens[pos + 2], "id") == 0 || strcmp(tokens[pos + 2], "num") == 0)) {
        match("id");
        match("=");
        if (strcmp(tokens[pos], "id") == 0 || strcmp(tokens[pos], "num") == 0)
            pos++;
        else
            error("id or num");
        match(";");
    } else {
        error("Assignment Statement (id = id/num;)");
    }
}

void identifier_list() {
    if (strcmp(tokens[pos], "id") == 0) {
        match("id");
        while (strcmp(tokens[pos], ",") == 0) {
            match(",");
            match("id");
        }
    } else {
        error("id");
    }
}

void data_type() {
    if (strcmp(tokens[pos], "int") == 0 || strcmp(tokens[pos], "char") == 0) {
        pos++;
    } else {
        error("int or char");
    }
}

void declaration() {
    if (strcmp(tokens[pos], "int") == 0 || strcmp(tokens[pos], "char") == 0) {
        data_type();
        identifier_list();
        match(";");
        declaration(); // Recursive call for next declaration
    }
    // else epsilon
}

void program() {
    match("main");
    match("(");
    match(")");
    match("{");
    declaration();
    assign_stat();
    match("}");
    if (strcmp(tokens[pos], "$") != 0) {
        error("End of Program");
    }
}

// --- Main Function ---

int main() {
    const char* input_code = "main() { int id, id2; char id3; id = num; }";

    lexer(input_code);
    printf("Parsing starts...\n");
    program();
    printf("Parsing successful. No syntax errors.\n");
    return 0;
}
