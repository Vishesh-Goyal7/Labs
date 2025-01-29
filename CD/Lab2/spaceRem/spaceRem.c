#include <stdio.h>
#include <stdlib.h>

void replaceSpacesAndTabs(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    char buffer[10000];  
    char ch, prev = 0;
    int index = 0;

    while ((ch = fgetc(file)) != EOF) {
        if ((ch == ' ' || ch == '\t') && (prev == ' ' || prev == '\t')) {
            continue;
        }
        if (ch == '\t') {
            ch = ' ';
        }
        buffer[index++] = ch;
        prev = ch;
    }
    buffer[index] = '\0';
    fclose(file);
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot write to file %s\n", filename);
        return;
    }
    fputs(buffer, file);
    fclose(file);

    printf("File updated successfully!\n");
}

int main() {
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    replaceSpacesAndTabs(filename);

    return 0;
}
