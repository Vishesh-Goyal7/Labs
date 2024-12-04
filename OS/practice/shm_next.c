#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct{
    char input; 
    char output;
}shmem;

int main(){

    key_t key = ftok("shm_next.c", 65);
    int shmid = shmget(key, sizeof(shmem), 0666|IPC_CREAT);
    shmem * data = (shmem*)shmat(shmid, NULL, 0);
    printf("Enter a character : ");
    scanf("%c", &data->input);

    pid_t pid = fork();

    if(pid < 0){
        printf("Fork failed\n");
        exit(1);
    } else if(pid == 0){
        if(data -> input == 'Z'){
            data -> output = 'A';
        } else if(data -> input == 'z'){
            data -> output = 'a';
        } else {
            char input = data -> input;
            data -> output = ++input;
        }
    } else {
        wait(NULL);
        printf("The next character is : %c", data -> output);
    }
}