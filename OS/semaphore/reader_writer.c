#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5 

int buffer[BUFFER_SIZE]; 
int count = 0;           

sem_t mutex;             
sem_t writeBlock;        
int readerCount = 0;     

void *writer(void *param) {
    for (int i = 0; i < 5; i++) { 
        sem_wait(&writeBlock);    

        int item = rand() % 100;
        buffer[count++] = item;
        printf("Writer wrote: %d\n", item);

        sem_post(&writeBlock);    
    }
    pthread_exit(0);
}

void *reader(void *param) {
    for (int i = 0; i < 5; i++) { 
        sem_wait(&mutex);          
        readerCount++;
        if (readerCount == 1) {
            sem_wait(&writeBlock); 
        }
        sem_post(&mutex);

        if (count > 0) {
            int item = buffer[count - 1];
            printf("Reader read: %d\n", item);
        } else {
            printf("Reader found the buffer empty.\n");
        }

        sem_wait(&mutex);          
        readerCount--;
        if (readerCount == 0) {
            sem_post(&writeBlock); 
        }
        sem_post(&mutex);
    }
    pthread_exit(0);
}

int main() {
    pthread_t writers[2], readers[3];

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}
