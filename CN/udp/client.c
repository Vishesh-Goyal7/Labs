#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024
#define MAX_ROWS 10
#define MAX_COLS 10

// Function to send matrix rows to the server
void send_matrix(int sockfd, struct sockaddr_in *server_addr) {
    char buffer[BUFFER_SIZE];
    int rows, cols;

    printf("Enter number of rows (max %d): ", MAX_ROWS);
    scanf("%d", &rows);
    printf("Enter number of columns (max %d): ", MAX_COLS);
    scanf("%d", &cols);

    if (rows > MAX_ROWS || cols > MAX_COLS) {
        printf("Matrix size exceeds allowed limits.\n");
        return;
    }

    // Send each row of the matrix to the server
    for (int i = 0; i < rows; i++) {
        printf("Enter row %d: ", i + 1);
        for (int j = 0; j < cols; j++) {
            scanf("%d", &((int*)buffer)[j]);
        }

        // Send the row to the server
        sendto(sockfd, buffer, sizeof(int) * cols, 0, (struct sockaddr*)server_addr, sizeof(*server_addr));
        printf("Row %d sent to server.\n", i + 1);
    }
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address setup
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid server IP address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Client is ready to send matrix rows to server.\n");

    // Send the matrix rows to the server
    send_matrix(sockfd, &server_addr);

    // Close the socket
    close(sockfd);
    return 0;
}
