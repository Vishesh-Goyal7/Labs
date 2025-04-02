#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file, *outputFile;
    char filename[100], outputFilename[100] = "output.txt";
    char line[1024];

    printf("Enter the filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Could not create file %s\n", outputFilename);
        fclose(file);
        return 1;
    }
    
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "#include", 8) != 0) {
            fputs(line, outputFile);
        }
    }
    fclose(file);
    fclose(outputFile);

    printf("Processed file saved as %s\n", outputFilename);
    return 0;
}

#include <math.h>