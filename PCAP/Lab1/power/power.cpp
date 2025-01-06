#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char** argv){

    int rank; 
    // // Method 1 : Hardcode
    // int x = 3;
    // MPI_Init(&argc, &argv);
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // double res = pow(x, rank);
    // printf("Process %d : pow(%d, %d) = %.2f\n\n", rank, x, rank, res);
    // MPI_Finalize();

    // Method 2 : Command Line input
    int x = atoi(argv[1]);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double res = pow(x, rank);
    printf("Process %d : pow(%d, %d) = %.2f\n\n", rank, x, rank, res);
    MPI_Finalize();

    // // Method 3 : Scanf input
    // int x;
    // MPI_Init(&argc, &argv);
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // if(rank == 0){
    //     printf("Enter x value : ");
    //     scanf("%d", &x);
    // }
    // MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // double res = pow(x, rank);
    // printf("Process %d : pow(%d, %d) = %.2f\n\n", rank, x, rank, res);
    // MPI_Finalize();

    return 0;
}