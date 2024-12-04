#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


struct message {
    long msg_type;  
    int number;     
};

int is_palindrome(int num) {
    int original = num, reversed = 0, remainder;
    while (num != 0) {
        remainder = num % 10;
        reversed = reversed * 10 + remainder;
        num /= 10;
    }
    return original == reversed;
}

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

    if (msgrcv(msgid, &msg, sizeof(msg.number), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Process B: Received number %d from Process A\n", msg.number);

    if (is_palindrome(msg.number)) {
        printf("Process B: The number %d is a palindrome.\n", msg.number);
    } else {
        printf("Process B: The number %d is not a palindrome.\n", msg.number);
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    return 0;
}
