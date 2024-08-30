//calculator

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    int num1, num2, result;
    char operator;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    printf("Enter operation (+, -, *, /): ");
    scanf(" %c", &operator);

    num1 = htonl(num1);
    num2 = htonl(num2);

    send(sock, &num1, sizeof(int), 0);
    send(sock, &num2, sizeof(int), 0);
    send(sock, &operator, sizeof(char), 0);

    int valread = read(sock, buffer, BUFFER_SIZE);

    if (valread > 0) {
        if (buffer[0] == 'E') {
            printf("%s\n", buffer);
        } else {
            memcpy(&result, buffer, sizeof(int));
            result = ntohl(result);
            printf("Result: %d\n", result);
        }
    }
    close(sock);

    return 0;
}
