#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <set of strings>\n", argv[0]);
        return 1;
    }

    int num_strings = argc - 1;
    char** strings = argv + 1;  

    pid_t pid = fork();  

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        printf("Child process (sorted strings):\n");
        qsort(strings, num_strings, sizeof(char*), compare);
        for (int i = 0; i < num_strings; i++) {
            printf("%s\n", strings[i]);
        }

        exit(0); 
    } else {
        wait(NULL);
        printf("Parent process (unsorted strings):\n");
        for (int i = 0; i < num_strings; i++) {
            printf("%s\n", strings[i]);
        }
    }

    return 0;
}

// CLI Commands : 
// gcc -o q2 q2.c
// ./q2 hey hi hello bye
