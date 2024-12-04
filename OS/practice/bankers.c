#include <stdio.h>
#include <stdlib.h>

#define P 5
#define R 3

int main(){
    int max[P][R] = {{7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3}};
    int allocated[P][R] = {{0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2}};
    int available[R] = {3,3,2};
    int need[P][R];

    int count = 0;
    int process_q[P] = {-1};
    int status[P];

    for(int i = 0; i < P; i++){
        status[i] = 0;
        for(int j = 0; j < R; j++){
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    while(count < P){
        int safe = 0;
        for(int i = 0; i < P; i++){
            if(!status[i]){
                int can_finish = 1;
                for(int j = 0; j < R; j++){
                    if(need[i][j] > available[j]){
                        can_finish = 0;
                        break;
                    }
                }
                if(can_finish){
                    status[i] = 1;
                    for(int j = 0; j < R; j++){
                        available[j] += allocated[i][j];
                        allocated[i][j] = 0;
                    }
                    safe = 1;
                    process_q[count++] = i;
                }
            }
        }
        if(!safe){
            printf("System is not in a safe state. Resource deficit");
            break;
        }
    }
    printf("Safe state is possible by process sequence : ");
    for(int i = 0; i < P; i++){
        printf("%d\t", process_q[i]);
    }
}