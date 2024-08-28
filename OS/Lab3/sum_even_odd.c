#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int* array;
    int length;
    int sum;
} ThreadData;

void* sum_even(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int sum = 0;

    for (int i = 0; i < data->length; i++) {
        if (data->array[i] % 2 == 0) {
            sum += data->array[i];
        }
    }

    data->sum = sum;
    pthread_exit(NULL);
}

void* sum_odd(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int sum = 0;

    for (int i = 0; i < data->length; i++) {
        if (data->array[i] % 2 != 0) {
            sum += data->array[i];
        }
    }

    data->sum = sum;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <array of integers>\n", argv[0]);
        return 1;
    }

    int length = argc - 1;
    int* array = (int*)malloc(length * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < length; i++) {
        array[i] = atoi(argv[i + 1]);
    }

    ThreadData evenData = {array, length, 0};
    ThreadData oddData = {array, length, 0};

    pthread_t even_thread, odd_thread;
    int ret1 = pthread_create(&even_thread, NULL, sum_even, &evenData);
    int ret2 = pthread_create(&odd_thread, NULL, sum_odd, &oddData);

    if (ret1 != 0 || ret2 != 0) {
        printf("Error creating threads.\n");
        free(array);
        return 1;
    }

    pthread_join(even_thread, NULL);
    pthread_join(odd_thread, NULL);

    printf("Sum of even numbers: %d\n", evenData.sum);
    printf("Sum of odd numbers: %d\n", oddData.sum);

    free(array);

    return 0;
}

// Commands to run on cli : 
// gcc -pthread -o sum_even_odd sum_even_odd.c
// ./sum_even_odd 1 2 3 4 5 6 7 8 9 10