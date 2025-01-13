#include <stdio.h>
#include <mpi.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char* c){
    if (isupper(*c)) {
        *c = tolower(*c);  
    } else if (islower(*c)) {
        *c = toupper(*c);  
    }
}

int main(int argc, char** argv){

    int rank, size, strlength;
    char str[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strlength = strlen(str);
    }
    MPI_Bcast(&strlength, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&str, sizeof(str), MPI_CHAR, 0, MPI_COMM_WORLD);
    
    if (rank < strlength) {
        toggle_case(&str[rank]);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Process %d: Modified string: %s\n", rank, str);

    MPI_Finalize();
}