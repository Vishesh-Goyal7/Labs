#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){

    int rank, size;
    int num1, num2;
    double res;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        scanf("%d", &num1);
        scanf("%d", &num2);
    }

    MPI_Bcast(&num1, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&num2, 1, MPI_INT, 0, MPI_COMM_WORLD);

    switch(rank){
        case 1:
            res = num1 + num2;
            printf("Process %d : Addition : %d + %d = %.2f\n", rank, num1, num2, res);
            break;

        case 2:
            res = num1 - num2;
            printf("Process %d : Subtraction : %d - %d = %.2f\n", rank, num1, num2, res);
            break;

        case 3:
            res = num1 * num2;
            printf("Process %d : Multiplication : %d * %d = %.2f\n", rank, num1, num2, res);
            break;

        case 4:
            if(num2 == 0){
                printf("Division by 0 not possible");
                break;
            }
            res = num1 / num2;
            printf("Process %d : Division : %d / %d = %.2f\n", rank, num1, num2, res);
            break;

        default:
            printf("No op assigned. Process %d\n\n", rank);
            break;
    }

    MPI_Finalize();
}