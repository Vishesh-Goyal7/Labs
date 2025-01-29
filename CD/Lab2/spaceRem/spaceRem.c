#include <stdio.h>
#include <stdlib.h>

void replaceSpacesAndTabs(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    // Read the file into a buffer
    char buffer[10000];  // Large enough buffer to hold the file contents
    char ch, prev = 0;
    int index = 0;

    while ((ch = fgetc(file)) != EOF) {
        // If the current character is a space or a tab, and the previous one was also a space, skip it
        if ((ch == ' ' || ch == '\t') && (prev == ' ' || prev == '\t')) {
            continue;
        }
        // Convert tabs to spaces
        if (ch == '\t') {
            ch = ' ';
        }
        buffer[index++] = ch;
        prev = ch;
    }
    buffer[index] = '\0';  // Null-terminate the string
    fclose(file);

    // Write the modified content back to the same file
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
