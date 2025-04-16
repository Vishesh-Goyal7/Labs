#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int tempCount = 1;

char* newTemp() {
    static char temp[10];
    sprintf(temp, "T%d", tempCount++);
    return strdup(temp);
}

typedef struct {
    char* items[MAX];
    int top;
} Stack;

void push(Stack* s, char* val) {
    s->items[++s->top] = val;
}

char* pop(Stack* s) {
    if (s->top == -1) return NULL;
    return s->items[s->top--];
}

void generateAssembly(char op, char* op1, char* op2, char* result) {
    printf("MOV R0, %s\n", op1);
    switch(op) {
        case '+': printf("ADD R0, %s\n", op2); break;
        case '-': printf("SUB R0, %s\n", op2); break;
        case '*': printf("MUL R0, %s\n", op2); break;
        case '/': printf("DIV R0, %s\n", op2); break;
    }
    printf("MOV %s, R0\n", result);
}

void generateCodeFromPostfix(char* postfix) {
    Stack s;
    s.top = -1;
    char *op1, *op2, *result;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];
        if (isspace(token)) continue;

        if (isalnum(token)) {
            char* operand = (char*)malloc(2);
            operand[0] = token;
            operand[1] = '\0';
            push(&s, operand);
        } else if (strchr("+-*/", token)) {
            op2 = pop(&s);
            op1 = pop(&s);
            result = newTemp();
            generateAssembly(token, op1, op2, result);
            push(&s, result);
        } else {
            printf("Invalid character: %c\n", token);
            return;
        }
    }

    char* finalResult = pop(&s);
    printf("Final Result stored in: %s\n", finalResult);
}

int main() {
    char postfix[100];
    printf("Enter postfix expression (e.g., ab+cd-*): ");
    scanf("%s", postfix);

    printf("\n--- Assembly Code ---\n");
    generateCodeFromPostfix(postfix);
    return 0;
}