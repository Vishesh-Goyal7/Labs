#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to compare two strings (used for sorting)
int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <set of strings>\n", argv[0]);
        return 1;
    }

    // Store the command line arguments (strings)
    int num_strings = argc - 1;
    char** strings = argv + 1;  // Skip the program name

    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        // Fork failed
        printf("Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        // Child process: Sort and display the strings
        printf("Child process (sorted strings):\n");

        // Sort the strings using qsort
        qsort(strings, num_strings, sizeof(char*), compare);

        // Display the sorted strings
        for (int i = 0; i < num_strings; i++) {
            printf("%s\n", strings[i]);
        }

        exit(0);  // Child process terminates
    } else {
        // Parent process: Wait for child to complete
        wait(NULL);

        // Display the unsorted strings
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