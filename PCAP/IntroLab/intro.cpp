#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    
    int rank, size;

    MPI_Init(&argc, &argv);
    printf("Hello World\n");
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Process id is %d out of %d processes\n\n", rank, size);
    MPI_Finalize();
    
    return 0;
}

// mpicc -o exe intro.cpp
// mpirun -np 5 exe