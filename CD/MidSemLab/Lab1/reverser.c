#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *file, *revFile;
    char filename[100], revFilename[100] = "reversed.txt";
    char ch;
    long fileSize;
    printf("Enter the filename: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }
    revFile = fopen(revFilename, "w");
    if (revFile == NULL) {
        printf("Could not create file %s\n", revFilename);
        fclose(file);
        return 1;
    }
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    printf("Size of the file: %ld bytes\n", fileSize);
        for (long i = fileSize - 1; i >= 0; i--) {
        fseek(file, i, SEEK_SET);
        ch = fgetc(file);
        fputc(ch, revFile);
    }
    fclose(file);
    fclose(revFile);
    printf("File reversed and saved as %s\n", revFilename);
    return 0;
}