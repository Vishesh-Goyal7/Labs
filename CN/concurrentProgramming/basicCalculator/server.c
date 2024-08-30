// calculator

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
int perform_operation(int num1, int num2, char operator, int *result) {
    switch (operator) {
        case '+':
            *result = num1 + num2;
            return 0;
        case '-':
            *result = num1 - num2;
            return 0;
        case '*':
            *result = num1 * num2;
            return 0;
        case '/':
            if (num2 == 0) {
                return -1; 
            }
            *result = num1 / num2;
            return 0;
        default:
            return -2; 
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Math server is listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        int num1, num2, result;
        char operator;

        read(new_socket, &num1, sizeof(int));
        read(new_socket, &num2, sizeof(int));
        read(new_socket, &operator, sizeof(char));

        num1 = ntohl(num1);
        num2 = ntohl(num2);

        int status = perform_operation(num1, num2, operator, &result);

        if (status == 0) {
            result = htonl(result);
            send(new_socket, &result, sizeof(int), 0);
        } else if (status == -1) {
            char *error_msg = "Error: Division by zero!";
            send(new_socket, error_msg, strlen(error_msg), 0);
        } else if (status == -2) {
            char *error_msg = "Error: Invalid operator!";
            send(new_socket, error_msg, strlen(error_msg), 0);
        }
        close(new_socket);
    }

    return 0;
}
