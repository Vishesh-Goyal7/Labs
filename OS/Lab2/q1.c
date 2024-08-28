#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
    } else {
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());

        wait(NULL);
    }

    return 0;
}

// CLI Commands : 
// gcc -o q1 q1.c
// ./q1