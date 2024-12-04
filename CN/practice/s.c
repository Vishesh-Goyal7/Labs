#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define BUFFER 1024

int main(){
    int new_sock, server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server listening on %d\n", PORT);
    while(1){
        new_sock = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        int valread = read(new_sock, buffer, BUFFER);
        printf("Server received : %s\n", buffer);
        for(int i = 0; i < strlen(buffer); i++){
            if((buffer[i] >= 97 && buffer[i] <= 122) || (buffer[i] >= 65 && buffer[i] <= 90)){
                buffer[i] -= 4;
            }
        }
        printf("Decrypted message : %s", buffer);
        close(new_sock);
        memset(buffer, 0, BUFFER);
    }
    close(server_fd);
}