#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;  
sem_t mutex;     
int reader_count = 0; 

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&rw_mutex);  
        }
        sem_post(&mutex);  

        printf("Reader %d is reading the resource.\n", id);
        sleep(1);  

        sem_wait(&mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);  

        sleep(1);  
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&rw_mutex);  

        printf("Writer %d is writing to the resource.\n", id);
        sleep(1);  

        sem_post(&rw_mutex);

        sleep(1);  
    }
}

int main() {
    pthread_t r_threads[5], w_threads[5];
    int r_ids[5] = {1, 2, 3, 4, 5};
    int w_ids[5] = {1, 2, 3, 4, 5};

    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);   

    for (int i = 0; i < 5; i++) {
        pthread_create(&r_threads[i], NULL, reader, &r_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&w_threads[i], NULL, writer, &w_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(r_threads[i], NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(w_threads[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
