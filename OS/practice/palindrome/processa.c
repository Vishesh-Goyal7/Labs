#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct{
    long type;
    int num;
} msgq;

int main(){
    
    key_t key = ftok("processa.c", 97);
    int msgid = msgget(key, 0666|IPC_CREAT);
    msgq data;
    data.type = 1;
    printf("Enter number for palinddrome check : ");
    scanf("%d", &data.num);

    msgsnd(msgid, &data, sizeof(data.num), 0);
}