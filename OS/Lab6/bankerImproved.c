#include <stdio.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int isSafe(int processes[], int avail[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES]) {
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];

    for (int i = 0; i < MAX_RESOURCES; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < MAX_PROCESSES) {
        int found = 0;
        for (int p = 0; p < MAX_PROCESSES; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == MAX_RESOURCES) {
                    for (int k = 0; k < MAX_RESOURCES; k++)
                        work[k] += alloc[p][k];

                    safeSequence[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is not in a safe state\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < MAX_PROCESSES; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");
    return 1;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {3, 3, 2};
    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int alloc[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int need[MAX_PROCESSES][MAX_RESOURCES];

    for (int i = 0; i < MAX_PROCESSES; i++)
        for (int j = 0; j < MAX_RESOURCES; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    isSafe(processes, avail, max, alloc, need);

    return 0;
}
