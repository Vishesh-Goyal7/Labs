#include <stdio.h>
#include <mpi.h>

int fact(int num){
    if(num <= 1){
        return 1;
    }
    return num*fact(num-1);
}

int fib(int num){
    if(num <= 1){
        return num;
    }
    return (fib(num - 1) + fib(num - 2));
}

int main(int argc, char** argv){

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank%2 == 0){
        printf("Process %d : Factorial is : %d\n", rank, fact(rank));
    } else {
        printf("Process %d : Fibonacci is : %d\n", rank, fib(rank));
    }

    MPI_Finalize();
}