#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *file1, *file2, *resultFile;
    char filename1[100], filename2[100], resultFilename[100] = "merged.txt";
    char line1[256], line2[256];
    int read1, read2;
    printf("Enter first filename: ");
    scanf("%s", filename1);
    printf("Enter second filename: ");
    scanf("%s", filename2);
    file1 = fopen(filename1, "r");
    if (file1 == NULL) {
        printf("Could not open file %s\n", filename1);
        return 1;
    }
    file2 = fopen(filename2, "r");
    if (file2 == NULL) {
        printf("Could not open file %s\n", filename2);
        fclose(file1);
        return 1;
    }

    resultFile = fopen(resultFilename, "w");
    if (resultFile == NULL) {
        printf("Could not create file %s\n", resultFilename);
        fclose(file1);
        fclose(file2);
        return 1;
    }
    while (1) {
        read1 = (fgets(line1, sizeof(line1), file1) != NULL);
        read2 = (fgets(line2, sizeof(line2), file2) != NULL);
        if (!read1 && !read2) 
            break;
        if (read1)
            fputs(line1, resultFile);       
        if (read2)
            fputs(line2, resultFile);
    }
    fclose(file1);
    fclose(file2);
    fclose(resultFile);
    printf("Files merged alternatively and saved as %s\n", resultFilename);
    return 0;
}