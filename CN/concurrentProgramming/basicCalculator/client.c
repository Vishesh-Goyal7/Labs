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

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Get input from the user
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    printf("Enter operation (+, -, *, /): ");
    scanf(" %c", &operator);

    // Convert the numbers to network byte order before sending
    num1 = htonl(num1);
    num2 = htonl(num2);

    // Send the numbers and operator to the server
    send(sock, &num1, sizeof(int), 0);
    send(sock, &num2, sizeof(int), 0);
    send(sock, &operator, sizeof(char), 0);

    // Receive the result or error message from the server
    int valread = read(sock, buffer, BUFFER_SIZE);

    // Check if it's a result or an error message
    if (valread > 0) {
        if (buffer[0] == 'E') {
            // Print the error message
            printf("%s\n", buffer);
        } else {
            // Convert the result from network byte order to host byte order
            memcpy(&result, buffer, sizeof(int));
            result = ntohl(result);
            printf("Result: %d\n", result);
        }
    }

    // Close the connection
    close(sock);

    return 0;
}
