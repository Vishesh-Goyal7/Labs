#include <stdio.h>
#include <stdbool.h>

int n, m; 
int allocation[10][10], max[10][10], need[10][10], available[10];

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
    int work[10], finish[10], safeSequence[10], index = 0;
    
    for (int i = 0; i < m; i++)
        work[i] = available[i];
    
    for (int i = 0; i < n; i++)
        finish[i] = 0;
    
    for (int count = 0; count < n; count++) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];
                    
                    safeSequence[index++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("The system is not in a safe state.\n");
            return false;
        }
    }
    
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");
    
    return true;
}

bool requestResources(int processID, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[processID][i]) {
            printf("Error: Requested more than needed.\n");
            return false;
        }
    }
    
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            printf("Resources not available.\n");
            return false;
        }
    }
    
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[processID][i] += request[i];
        need[processID][i] -= request[i];
    }
    
    if (isSafe()) {
        return true;
    } else {
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[processID][i] -= request[i];
            need[processID][i] += request[i];
        }
        printf("The system is not in a safe state after allocation. Request denied.\n");
        return false;
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);
    
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    
    printf("Enter the max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    
    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);
    
    calculateNeed();
    
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Check system safety\n");
        printf("2. Request resources for a process\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                isSafe();
                break;
            case 2: {
                int processID, request[10];
                printf("Enter the process number (0 to %d): ", n - 1);
                scanf("%d", &processID);
                printf("Enter the resource request:\n");
                for (int i = 0; i < m; i++)
                    scanf("%d", &request[i]);
                
                requestResources(processID, request);
                break;
            }
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
    
    return 0;
}
