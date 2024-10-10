#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
    int* primes;
    int count;
} PrimeData;

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void* generate_primes(void* arg) {
    PrimeData* data = (PrimeData*)arg;
    int start = data->start;
    int end = data->end;
    
    int index = 0;
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            data->primes[index++] = i;
        }
    }
    data->count = index;  
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <start> <end>\n", argv[0]);
        return 1;
    }

    int start = atoi(argv[1]);
    int end = atoi(argv[2]);

    if (start > end || start < 0) {
        printf("Invalid range. Please ensure start <= end and both are non-negative.\n");
        return 1;
    }

    int* primes = (int*)malloc((end - start + 1) * sizeof(int));
    if (primes == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    PrimeData data;
    data.start = start;
    data.end = end;
    data.primes = primes;
    data.count = 0;

    pthread_t thread;
    int ret = pthread_create(&thread, NULL, generate_primes, &data);
    if (ret != 0) {
        printf("Error creating thread.\n");
        free(primes);
        return 1;
    }

    pthread_join(thread, NULL);

    printf("Prime numbers between %d and %d:\n", start, end);
    for (int i = 0; i < data.count; i++) {
        printf("%d ", data.primes[i]);
    }
    printf("\n");

    free(primes);

    return 0;
}

// Commands to run on cli : 
// gcc -pthread -o prime_generator prime_generator.c
// ./prime_generator 10 50