#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turn_around_time;
};

void calculateWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

void calculateTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turn_around_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void sortProcessesByBurstTime(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].burst_time > proc[j].burst_time) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void printProcessDetails(struct Process proc[], int n) {
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burst_time, proc[i].waiting_time, proc[i].turn_around_time);
    }
}

void sjfScheduling(struct Process proc[], int n) {
    sortProcessesByBurstTime(proc, n);
    calculateWaitingTime(proc, n);
    calculateTurnAroundTime(proc, n);
    printProcessDetails(proc, n);
}

int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
    }
    
    do {
        printf("\nMenu:\n");
        printf("1. SJF Scheduling\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                sjfScheduling(proc, n);
                break;
            case 2:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter again.\n");
        }
    } while (choice != 2);
    
    return 0;
}
