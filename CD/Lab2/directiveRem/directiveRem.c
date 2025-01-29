#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removePreprocessorDirectives(const char *inputFile, const char *outputFile) {
    FILE *input = fopen(inputFile, "r");
    if (input == NULL) {
        printf("Error: Cannot open file %s\n", inputFile);
        return;
    }

    FILE *output = fopen(outputFile, "w");
    if (output == NULL) {
        printf("Error: Cannot create output file %s\n", outputFile);
        fclose(input);
        return;
    }

    char line[1024]; 

    while (fgets(line, sizeof(line), input) != NULL) {
        if (line[0] != '#') {
            fputs(line, output);
        }
    }

    fclose(input);
    fclose(output);
    printf("Preprocessor directives removed. Output stored in %s\n", outputFile);
}

int main() {
    char inputFile[100], outputFile[100];

    printf("Enter the input C file: ");
    scanf("%s", inputFile);

    printf("Enter the output file: ");
    scanf("%s", outputFile);

    removePreprocessorDirectives(inputFile, outputFile);

    return 0;
}
