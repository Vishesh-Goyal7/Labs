#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resource types

int main() {
    // Initializing the Allocation matrix
    int allocation[P][R] = {{0, 1, 0}, 
                            {2, 0, 0}, 
                            {3, 0, 2}, 
                            {2, 1, 1}, 
                            {0, 0, 2}};

    // Initializing the Max matrix
    int max[P][R] = {{7, 5, 3}, 
                     {3, 2, 2}, 
                     {9, 0, 2}, 
                     {2, 2, 2}, 
                     {4, 3, 3}};

    // Initializing the Available resources array
    int available[R] = {3, 3, 2};

    // Declaring the Need matrix
    int need[P][R];

    // Calculating the Need matrix (Need = Max - Allocation)
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Marking all processes as unfinished initially
    bool finished[P] = {false};
    int safeSequence[P]; // To store the safe sequence
    int work[R];         // Work array to store temporary available resources

    // Initializing work as available
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0; // Count of processes that have finished execution

    while (count < P) {
        bool foundProcess = false;

        // Find a process that can finish with the current available resources
        for (int i = 0; i < P; i++) {
            if (!finished[i]) {
                bool canFinish = true;

                // Check if the process needs less or equal resources than available (work)
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                // If the process can finish
                if (canFinish) {
                    // Mark the process as finished
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j]; // Free the resources
                    }

                    safeSequence[count++] = i; // Add this process to the safe sequence
                    finished[i] = true;         // Mark the process as finished
                    foundProcess = true;        // Set the flag indicating a process has been found
                }
            }
        }

        // If no such process is found, the system is in an unsafe state (deadlock).
        if (!foundProcess) {
            printf("The system is in an unsafe state.\n");
            return -1;
        }
    }

    // If the loop completes, the system is in a safe state, and we print the safe sequence
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return 0;
}
