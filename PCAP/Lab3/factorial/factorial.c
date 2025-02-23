#include <stdio.h>
#include <mpi.h>

long long factorial(int num) {
    long long fact = 1;
    for (int i = 2; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

int main(int argc, char** argv) {
    int rank, size, n;
    int num;
    long long fact, sum = 0;

    MPI_Init(&argc, &argv);               
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int numbers[size];
    if (rank == 0) {
        printf("Enter %d numbers: ", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &numbers[i]);
        }
    }
    MPI_Scatter(numbers, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);

    fact = factorial(num);

    MPI_Reduce(&fact, &sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of factorials: %lld\n", sum);
    }

    MPI_Finalize(); 
    return 0;
}
