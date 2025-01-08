#include <stdio.h>
#include <stdlib.h>

void merger(char *in1, char *in2, char *res) {
    FILE *input1 = fopen(in1, "r");
    if (input1 == NULL) {
        printf("File %s not found, quitting.\n", in1);
        return;
    }

    FILE *input2 = fopen(in2, "r");
    if (input2 == NULL) {
        printf("File %s not found, quitting.\n", in2);
        fclose(input1);
        return;
    }

    FILE *output = fopen(res, "w");
    if (output == NULL) {
        printf("Could not create output file %s, quitting.\n", res);
        fclose(input1);
        fclose(input2);
        return;
    }

    char line[2048];

    // Read lines alternately from the files
    while (1) {
        if (fgets(line, sizeof(line), input1) != NULL) {
            fputs(line, output);
        }
        if (fgets(line, sizeof(line), input2) != NULL) {
            fputs(line, output);
        }

        if (feof(input1) && feof(input2)) {
            break;
        }
    }

    fclose(input1);
    fclose(input2);
    fclose(output);
    printf("Lines merged successfully into %s.\n", res);
}

int main() {
    char in1[100], in2[100], out[100];

    printf("Enter file 1 for the operation: ");
    scanf("%s", in1);

    printf("Enter file 2 for the operation: ");
    scanf("%s", in2);

    printf("Enter output file for the operation: ");
    scanf("%s", out);

    merger(in1, in2, out);

    return 0;
}
