#include <stdio.h>
#include <stdlib.h>

void counter(const char* name){
    FILE *file = fopen(name, "r");
    
    if(file == NULL){
        printf("File doesn't exist. \n\n Closing operation. \n");
        return;
    }

    int lines = 0;
    int characters = 0;
    char ch;

    while((ch = fgetc(file)) != EOF){
        characters++;
        if(ch == '\n') lines++;
    }

    fclose(file);

    printf("For the given file, there are %d characters and %d lines. ", characters, lines);

    return;
}

int main(){

    char filename[300];

    printf("Enter file for the operation : ");
    scanf("%s", filename);

    counter(filename);

    return 0;
}