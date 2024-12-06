#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_ROWS 10
#define MAX_COLS 10

// Function to receive the matrix rows from the client
void receive_matrix(int sockfd, struct sockaddr_in *client_addr) {
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(*client_addr);
    int rows_received = 0;
    int matrix[MAX_ROWS][MAX_COLS];

    printf("Waiting to receive matrix rows...\n");

    while (rows_received < MAX_ROWS) {
        // Receive a row of the matrix from the client
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)client_addr, &addr_len);

        // Convert the received row (as a string) into an integer array
        char* token = strtok(buffer, " ");
        int col_index = 0;
        while (token != NULL) {
            matrix[rows_received][col_index] = atoi(token);  // Convert string to int and store
            col_index++;
            token = strtok(NULL, " ");
        }

        printf("Received row %d: ", rows_received + 1);
        for (int i = 0; i < col_index; i++) {
            printf("%d ", matrix[rows_received][i]);
        }
        printf("\n");

        rows_received++;
    }

    // Print the complete matrix after receiving all rows
    printf("\nReceived complete matrix:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address setup
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to the address and port
    if (bind(sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server is running on port %d\n", PORT);

    // Start receiving matrix rows from client
    receive_matrix(sockfd, &client_addr);

    // Close the socket
    close(sockfd);
    return 0;
}
