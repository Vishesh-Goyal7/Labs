#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int tempCount = 1;

typedef struct{
    char* arr[1000];
    int top;
} Stack;

void push(Stack* s, char* str){
    s->arr[++s->top] = str;
}

char* pop(Stack* s){
    if(s->top == -1) return NULL;
    return s->arr[s->top--];
}

char* newTemp(){
    static char temp[10];
    sprintf(temp, "T%d", tempCount++);
    return temp;
}

void assembly(char* op1, char* op2, char op, char* result){
    printf("MOV R0, %s\n", op1);
    switch(op){
        case '+' : printf("ADD R0, %s\n", op2); break;
        case '-' : printf("SUB R0, %s\n", op2); break;
        case '*' : printf("MUL R0, %s\n", op2); break;
        case '/' : printf("DIV R0, %s\n", op2); break;
    }
    printf("MOV %s, R0\n", result);
}

void AssemblyGen(char* exp){
    Stack s;
    s.top = -1;
    char *op1, *op2, *result;

    for(int i = 0; exp[i] != '\0'; i++){
        char token = exp[i];
        if(isspace(token)) continue;
        if(isalnum(token)){
            char* temp = (char*)malloc(2);
            temp[1] = '\0';
            temp[0] = token;
            push(&s, temp);
        } else if(strchr("+-*/", token)){
            char* op2 = pop(&s);
            char* op1 = pop(&s);
            char* result = newTemp();
            assembly(op1, op2, token, result);
            push(&s, result);
        }
    }
    printf("Final result stored in %s\n", pop(&s));
}

int main(){
    char exp[1000];
    printf("Enter postfix expression : ");
    scanf("%s", exp);
    AssemblyGen(exp);
}