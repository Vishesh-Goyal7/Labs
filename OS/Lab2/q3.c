#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void bubble_sort(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <set of strings>\n", argv[0]);
        return 1;
    }

    int num_strings = argc - 1;
    char **strings1 = malloc(num_strings * sizeof(char *));
    char **strings2 = malloc(num_strings * sizeof(char *));

    for (int i = 0; i < num_strings; i++) {
        strings1[i] = strdup(argv[i + 1]);
        strings2[i] = strdup(argv[i + 1]);
    }

    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0) {
        printf("Fork failed for child 1!\n");
        return 1;
    } else if (pid1 == 0) {
        printf("Child 1 (Bubble Sort):\n");
        bubble_sort(strings1, num_strings);
        for (int i = 0; i < num_strings; i++) {
            printf("%s\n", strings1[i]);
        }
        exit(0);
    } else {
        pid2 = fork();

        if (pid2 < 0) {
            printf("Fork failed for child 2!\n");
            return 1;
        } else if (pid2 == 0) {
            printf("Child 2 (Qsort):\n");
            qsort(strings2, num_strings, sizeof(char *), compare);
            for (int i = 0; i < num_strings; i++) {
                printf("%s\n", strings2[i]);
            }
            exit(0);
        } else {
            int status;
            pid_t completed_pid = wait(&status);
            printf("Parent: Child process with PID %d has completed.\n", completed_pid);

            wait(NULL);

            for (int i = 0; i < num_strings; i++) {
                free(strings1[i]);
                free(strings2[i]);
            }
            free(strings1);
            free(strings2);
        }
    }

    return 0;
}
