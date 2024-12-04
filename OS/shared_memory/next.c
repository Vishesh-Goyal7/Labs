#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>


struct shared_data {
    char parent_input;  
    char child_output;  
};

int main() {
    key_t key = ftok("next.c", 65);  
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int shmid = shmget(key, sizeof(struct shared_data), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    struct shared_data* data = (struct shared_data*)shmat(shmid, NULL, 0);
    if (data == (void*)-1) {
        perror("shmat failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        printf("Parent: Enter an English alphabet: ");
        scanf("%c", &data->parent_input);
        getchar();  

        wait(NULL);

        printf("Parent: The child responded with the letter: %c\n", data->child_output);

        if (shmdt(data) == -1) {
            perror("shmdt failed");
            exit(1);
        }

        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl failed");
            exit(1);
        }

    } else {
        sleep(1);  

        char input_char = data->parent_input;
        printf("Child: Received the letter: %c\n", input_char);

        if ((input_char >= 'a' && input_char < 'z') || (input_char >= 'A' && input_char < 'Z')) {
            data->child_output = input_char + 1;
        } else if (input_char == 'z') {
            data->child_output = 'a';
        } else if (input_char == 'Z') {
            data->child_output = 'A';
        }

        if (shmdt(data) == -1) {
            perror("shmdt failed");
            exit(1);
        }

        exit(0);
    }

    return 0;
}
