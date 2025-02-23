#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, m;
    double local_avg, global_sum;

    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the number of elements per process (m): ");
        scanf("%d", &m);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int total_elements = size * m;
    int numbers[total_elements];
    int recv_numbers[m];

    if (rank == 0) {
        printf("Enter %d elements: ", total_elements);
        for (int i = 0; i < total_elements; i++) {
            scanf("%d", &numbers[i]);
        }
    }
    MPI_Scatter(numbers, m, MPI_INT, recv_numbers, m, MPI_INT, 0, MPI_COMM_WORLD);

    double sum = 0.0;
    for (int i = 0; i < m; i++) {
        sum += recv_numbers[i];
    }
    local_avg = sum / m;

    MPI_Reduce(&local_avg, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double net_avg = global_sum / size;
        printf("Final average: %.2f\n", net_avg);
    }

    MPI_Finalize(); 
    return 0;
}
