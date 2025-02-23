#include <stdio.h>
#include <mpi.h>

int factorial(int num) {
    int fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

int main(int argc, char *argv[]) {
    int rank, size, fact, scan_sum, n, error_code;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter value of n (must be equal to number of processes): ");
        scanf("%d", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (n != size) {
        if (rank == 0) {
            printf("Error: Number of processes must be equal to n!\n");
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    fact = factorial(rank + 1);

    error_code = MPI_Scan(&fact, &scan_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (error_code != MPI_SUCCESS) {
        char error_string[100];
        int length_of_error_string;
        MPI_Error_string(error_code, error_string, &length_of_error_string);
        printf("Process %d: MPI_Scan error: %s\n", rank, error_string);
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
    if (rank == n - 1) {
        printf("Sum of factorials (1! + 2! + ... + %d!) = %d\n", n, scan_sum);
    }

    MPI_Finalize();
    return 0;
}
