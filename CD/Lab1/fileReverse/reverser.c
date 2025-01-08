#include <stdio.h>
#include <stdlib.h>

void reverseIt(char* inname, char* outname){

    FILE *input = fopen(inname, "r");
    if(input == NULL){
        printf("Can't open the file");
        return;
    }

    FILE *output = fopen(outname, "w");

    fseek(input, 0, SEEK_END);
    long filesize = ftell(input);

    for(long i = filesize - 1; i >= 0; i--){
        fseek(input, i, SEEK_SET);
        char ch = fgetc(input);
        fputc(ch, output);
    }

    fclose(input);
    fclose(output);

    printf("Operation complete, reversed file stored in %s", outname);

    return;
}

int main(){

    char in[100], out[100];

    printf("Enter input file name : ");
    scanf("%s", in);
    printf("Enter output file name : ");
    scanf("%s", out);

    reverseIt(in, out);

    return 0;
}