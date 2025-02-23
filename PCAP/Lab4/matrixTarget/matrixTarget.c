#include <stdio.h>
#include <mpi.h>

#define SIZE 9  

int main(int argc, char *argv[]) {
    int rank, size, matrix[SIZE], sub_array[SIZE / 3], target, local_count = 0, total_count;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 3) {
        if (rank == 0) {
            printf("Error: Please run with exactly 3 processes.\n");
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        printf("Enter a 3x3 matrix:\n");
        for (int i = 0; i < SIZE; i++) {
            scanf("%d", &matrix[i]);
        }

        printf("Enter target element to search: ");
        scanf("%d", &target);
    }

    MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(matrix, SIZE / 3, MPI_INT, sub_array, SIZE / 3, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < SIZE / 3; i++) {
        if (sub_array[i] == target) {
            local_count++;
        }
    }
    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total occurrences of %d in the matrix: %d\n", target, total_count);
    }

    MPI_Finalize();
    return 0;
}
