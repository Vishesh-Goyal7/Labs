#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
int prime_count = 0;
int start, end;

void* find_primes(void* arg) {
    int thread_id = *((int*)arg);
    int local_count = 0;

    // Determine the subrange for this thread
    int subrange_start = start + thread_id;
    int subrange_end = end;
    if (thread_id > 0) {
        subrange_start += thread_id; // Adjust start to avoid overlapping with previous thread
    }

    for (int num = subrange_start; num <= subrange_end; num += 2) {
        int is_prime = 1;

        // Check if num is a prime number
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime && num > 1) {
            local_count++;
            pthread_mutex_lock(&mutex);
            prime_count++;
            printf("Prime found by thread %d: %d\n", thread_id, num);
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit((void*) local_count);
}

int main() {
    int num_threads;
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    printf("Enter the starting point: ");
    scanf("%d", &start);

    printf("Enter the ending point: ");
    scanf("%d", &end);

    pthread_t threads[num_threads];
    int thread_ids[num_threads];

    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, find_primes, &thread_ids[i]);
    }

    // Join threads and accumulate local counts
    int total_primes = 0;
    void* thread_ret;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], &thread_ret);
        total_primes += (int) thread_ret;
    }

    printf("\nTotal prime numbers found: %d\n", prime_count);

    pthread_mutex_destroy(&mutex);
    return 0;
}
