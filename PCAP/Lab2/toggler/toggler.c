#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <ctype.h>

void toggle_case(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (islower(str[i]))
            str[i] = toupper(str[i]);
        else if (isupper(str[i]))
            str[i] = tolower(str[i]);
    }
}

int main(int argc, char** argv) {
    int rank;
    MPI_Status status;

    MPI_Init(&argc, &argv);               
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    if (rank == 0) {
        char word[100];
        char toggled_word[100];

        printf("Enter a word: ");
        scanf("%s", word);
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("Process 0: Sent word '%s' to Process 1.\n", word);
        MPI_Recv(toggled_word, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
        printf("Process 0: Received toggled word '%s' from Process 1.\n", toggled_word);

    } else if (rank == 1) {
        char received_word[100];
        MPI_Recv(received_word, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process 1: Received word '%s' from Process 0.\n", received_word);
        toggle_case(received_word);
        MPI_Ssend(received_word, strlen(received_word) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
        printf("Process 1: Sent toggled word '%s' back to Process 0.\n", received_word);
    }
    MPI_Finalize();
    return 0;
}
