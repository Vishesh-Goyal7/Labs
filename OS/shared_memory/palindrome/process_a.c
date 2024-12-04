#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


struct message {
    long msg_type;  
    int number;     
};

int main() {
    key_t key = ftok("process_a.c", 65);  
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    struct message msg;
    msg.msg_type = 1;  
    msg.number = 12321;  

    if (msgsnd(msgid, &msg, sizeof(msg.number), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Process A: Sent number %d to Process B\n", msg.number);

    return 0;
}
