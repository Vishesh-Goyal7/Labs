#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turn_around_time;
};

void calculateWaitingTime(struct Process proc[], int n, int quantum) {
    int time = 0, done;
    
    do {
        done = 1; // Assume all processes are done
        
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                done = 0; // There is a pending process
                
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst_time;
                    proc[i].remaining_time = 0;
                }
            }
        }
    } while (!done);
}

void calculateTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turn_around_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void printProcessDetails(struct Process proc[], int n) {
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burst_time, proc[i].waiting_time, proc[i].turn_around_time);
    }
}

void roundRobinScheduling(struct Process proc[], int n, int quantum) {
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
    }
    
    calculateWaitingTime(proc, n, quantum);
    calculateTurnAroundTime(proc, n);
    printProcessDetails(proc, n);
}

int main() {
    int n, quantum, choice;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
    }
    
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    
    do {
        printf("\nMenu:\n");
        printf("1. Round Robin Scheduling\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                roundRobinScheduling(proc, n, quantum);
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
