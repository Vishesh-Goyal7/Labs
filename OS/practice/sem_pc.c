#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER 5

sem_t empty, full;
pthread_mutex_t mutex;

int buffer[BUFFER];
int in = 0; out = 0;

void* producer(void* param){
    while(1){
       int item = rand()%100;
       sem_wait(&empty);
       pthread_mutex_lock(&mutex);
       buffer[in] = item;
       in = (in+1)%BUFFER;
       printf("Producer produced : %d", item);
       pthread_mutex_unlock(&mutex);
       sem_post(&full); 
    }
    sleep(1);
    pthread_exit(1);
}

void* consumer(void* param){
    while(1){
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        out = (out+1)%BUFFER;
        printf("Consumer used : %d", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    sleep(1);
    pthread_exit(1);
}

int main(){
    pthread_t consumert, producert;

    sem_init(&empty, 0, BUFFER);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producert, NULL, producer, NULL);
    pthread_create(&consumert, NULL, consumer, NULL);
    
    pthread_join(producert, NULL);
    pthread_join(consumert, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
}