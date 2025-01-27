#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, number;

    MPI_Init(&argc, &argv);               
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if (rank == 0) {
        printf("Enter a number: ");
        scanf("%d", &number);
        printf("Root Process (0): Sending number %d to Process 1\n", number);
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&number, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Root Process (0): Received final number %d from Process %d\n", number, size - 1);
    } else {
        MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d: Received number %d from Process %d\n", rank, number, rank - 1);
        number += 1;
        int next_process = (rank + 1) % size; 
        MPI_Send(&number, 1, MPI_INT, next_process, 0, MPI_COMM_WORLD);
        printf("Process %d: Sent number %d to Process %d\n", rank, number, next_process);
    }

    MPI_Finalize(); 
    return 0;
}
