#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER 1024

int main(){
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUFFER];
    char buffer[BUFFER] = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    printf("Enter message to encrypt : ");
    fgets(message, BUFFER, stdin);
    message[strcspn(message, "\n")] = 0;
    for(int i = 0; i < strlen(message); i++){
        if((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122)){
            message[i] += 4;
        }
    }
    send(sock, message, strlen(message), 0);
    close(sock);
}