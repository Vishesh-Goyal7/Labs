#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int labelCount = 0, tempCount = 0;

char* newLabel() {
    static char lbl[10];
    sprintf(lbl, "L%d", labelCount++);
    return strdup(lbl);
}

char* newTemp() {
    static char tmp[10];
    sprintf(tmp, "t%d", tempCount++);
    return strdup(tmp);
}

void generateAssignment(char* lhs, char* rhs) {
    printf("%s = %s\n", lhs, rhs);
}

void generateConditional(char* cond, char* trueLabel) {
    printf("if %s goto %s\n", cond, trueLabel);
}

void generateGoto(char* label) {
    printf("goto %s\n", label);
}

void generateLabel(char* label) {
    printf("%s:\n", label);
}

void processLine(char* line) {
    if (strncmp(line, "if", 2) == 0) {
        char cond[50], stmt[50];
        sscanf(line, "if (%[^)]) %[^;];", cond, stmt);

        char* trueLbl = newLabel();
        char* endLbl = newLabel();

        generateConditional(cond, trueLbl);
        generateGoto(endLbl);
        generateLabel(trueLbl);
        generateAssignment(strtok(stmt, "="), strtok(NULL, "="));
        generateLabel(endLbl);
    }

    else if (strncmp(line, "if", 2) == 0 && strstr(line, "else")) {
        char cond[50], stmt1[50], stmt2[50];
        sscanf(line, "if (%[^)]) %[^;]; else %[^;];", cond, stmt1, stmt2);

        char* trueLbl = newLabel();
        char* falseLbl = newLabel();
        char* endLbl = newLabel();

        generateConditional(cond, trueLbl);
        generateGoto(falseLbl);

        generateLabel(trueLbl);
        generateAssignment(strtok(stmt1, "="), strtok(NULL, "="));
        generateGoto(endLbl);

        generateLabel(falseLbl);
        generateAssignment(strtok(stmt2, "="), strtok(NULL, "="));

        generateLabel(endLbl);
    }

    else if (strncmp(line, "while", 5) == 0) {
        char cond[50], stmt[50];
        sscanf(line, "while (%[^)]) %[^;];", cond, stmt);

        char* startLbl = newLabel();
        char* trueLbl = newLabel();
        char* endLbl = newLabel();

        generateLabel(startLbl);
        generateConditional(cond, trueLbl);
        generateGoto(endLbl);

        generateLabel(trueLbl);
        generateAssignment(strtok(stmt, "="), strtok(NULL, "="));
        generateGoto(startLbl);

        generateLabel(endLbl);
    }

    else if (strchr(line, '=')) {
        char* lhs = strtok(line, "=");
        char* rhs = strtok(NULL, ";");

        if (strchr(rhs, '+') || strchr(rhs, '-') || strchr(rhs, '*') || strchr(rhs, '/')) {
            char* op1 = strtok(rhs, "+-*/");
            char* op = rhs + strlen(op1);
            char* op2 = op + 1;

            char* tmp = newTemp();
            printf("%s = %s %c %s\n", tmp, op1, *op, op2);
            printf("%s = %s\n", lhs, tmp);
        } else {
            printf("%s = %s\n", lhs, rhs);
        }
    }
}
  
int main() {
    char line[100];

    printf("Enter C-like code (1 statement per line, 'end' to stop):\n");
    while (1) {
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0; // remove newline
        if (strcmp(line, "end") == 0) break;
        processLine(line);
    }

    return 0;
}
