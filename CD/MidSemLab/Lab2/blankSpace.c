#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file, *outputFile;
    char filename[100], outputFilename[100] = "output.txt";
    char ch, prev = 'a'; 

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
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\t') {
            if (prev != ' ') { 
                fputc(' ', outputFile);
            }
        } else {
            fputc(ch, outputFile);
        }
        prev = ch;
    }
    fclose(file);
    fclose(outputFile);
    printf("Processed file saved as %s\n", outputFilename);
    return 0;
}