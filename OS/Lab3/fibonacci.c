#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *fibonacci;  
    int n;           
} FibonacciData;

void* generate_fibonacci(void* arg) {
    FibonacciData* data = (FibonacciData*)arg;
    int n = data->n;
    data->fibonacci[0] = 0;

    if (n > 1) {
        data->fibonacci[1] = 1;
    }

    for (int i = 2; i < n; i++) {
        data->fibonacci[i] = data->fibonacci[i-1] + data->fibonacci[i-2];
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number of Fibonacci numbers>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    int* fibonacci = (int*)malloc(n * sizeof(int));
    if (fibonacci == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    FibonacciData data;
    data.fibonacci = fibonacci;
    data.n = n;

    pthread_t thread;
    int ret = pthread_create(&thread, NULL, generate_fibonacci, &data);
    if (ret != 0) {
        printf("Error creating thread.\n");
        free(fibonacci);
        return 1;
    }

    pthread_join(thread, NULL);

    printf("Fibonacci sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacci[i]);
    }
    printf("\n");

    free(fibonacci);

    return 0;
}


// Commands to run on cli : 
// gcc -pthread -o fibonacci fibonacci.c   
// ./fibonacci 10