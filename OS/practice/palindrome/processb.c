#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>

typedef struct{
    long type;
    int num;
} msgq;

int palindrome(int num){
    int original = num, reverse = 0;
    while(original != 0){
        reverse = reverse*10 + original%10;
        original /= 10;
    }
    return (num == reverse);
}

int main(){
    key_t key = ftok("processa.c", 97);
    int msgid = msgget(key, 0666|IPC_CREAT);
    msgq msg;
    msgrcv(msgid, &msg, sizeof(msg.num), 1, 0);
    int palin = palindrome(msg.num);
    if(palin){
        printf("number is a palindrome");
    }
    msgctl(msgid, IPC_RMID, NULL);

    printf("\n\nMessaage queue cleared and deleted");
}