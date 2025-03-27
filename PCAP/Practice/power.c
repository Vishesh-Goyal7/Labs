#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    const int N = 100; // Size of the array
    double array[N], local_sum = 0.0, global_sum = 0.0;
    int local_N;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    local_N = N / size; // Divide array among processes
    double local_array[local_N];

    if (rank == 0) {
        // Initialize the array
        for (int i = 0; i < N; i++) {
            array[i] = i + 1; // Example: array of numbers 1 to N
        }
    }

    // Scatter data to all processes
    MPI_Scatter(array, local_N, MPI_DOUBLE, local_array, local_N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    // Compute local sum
    for (int i = 0; i < local_N; i++) {
        local_sum += local_array[i];
    }
    
    // Reduce local sums to global sum at root
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        double average = global_sum / N;
        printf("Average of array: %f\n", average);
    }
    
    MPI_Finalize();
    return 0;
}