#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);               
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            int num_to_send = i * 10;
            MPI_Send(&num_to_send, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Master: Sent %d to process %d\n", num_to_send, i);
        }
    } else {
        int received_num;
        MPI_Recv(&received_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process %d: Received %d from master\n", rank, received_num);
    }

    MPI_Finalize();
    return 0;
}
