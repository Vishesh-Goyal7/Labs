#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <ctype.h>

#define MAX_LEN 1000

int is_vowel(char c) {
    char vowels[] = "AEIOUaeiou";
    for (int i = 0; i < 10; i++) {
        if (c == vowels[i]) return 1;
    }
    return 0; 
}

int main(int argc, char *argv[]) {
    int rank, size, local_count = 0, total_non_vowel = 0;
    char str[MAX_LEN], sub_str[MAX_LEN];
    int str_len, chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter a string (length must be divisible by %d): ", size);
        fgets(str, MAX_LEN, stdin);
        str_len = strlen(str);

        if (str[str_len - 1] == '\n') {
            str[str_len - 1] = '\0';
            str_len--;
        }

        if (str_len % size != 0) {
            printf("Error: String length is not divisible by number of processes!\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    MPI_Bcast(&str_len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    chunk_size = str_len / size;

    MPI_Scatter(str, chunk_size, MPI_CHAR, sub_str, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk_size; i++) {
        if (!is_vowel(sub_str[i]) && isalpha(sub_str[i])) {
            local_count++;
        }
    }
    MPI_Reduce(&local_count, &total_non_vowel, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total number of non-vowel characters: %d\n", total_non_vowel);
    }

    MPI_Finalize();
    return 0;
}
