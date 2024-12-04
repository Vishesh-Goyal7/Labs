#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  
#define NUM_WORDS 3    

struct shared_data {
    char words[NUM_WORDS][50];  
};

int main() {
    key_t key = ftok("prod_cons.c", 65);  
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    struct shared_data* data = (struct shared_data*)shmat(shmid, NULL, 0);
    if (data == (void*)-1) {
        perror("shmat failed");
        exit(1);
    }

    printf("Producer: Writing words to shared memory...\n");
    strcpy(data->words[0], "Hello");
    strcpy(data->words[1], "World");
    strcpy(data->words[2], "Shared Memory");

    sleep(1);

    printf("Consumer: Reading words from shared memory...\n");
    for (int i = 0; i < NUM_WORDS; i++) {
        printf("Consumer: Word %d: %s\n", i + 1, data->words[i]);
    }

    if (shmdt(data) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl failed");
        exit(1);
    }

    printf("Shared memory detached and deleted. Program terminating...\n");

    return 0;
}
