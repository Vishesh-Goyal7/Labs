#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void remove_duplicates(char *input, char *output) {
    char words[100][50];  // Array to store individual words
    int count[100] = {0}; // Array to store word counts
    int word_count = 0;
    
    char *token = strtok(input, " ");
    
    // Tokenize the input string into words
    while (token != NULL) {
        int found = 0;
        
        // Check if the word has already been seen
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                count[i]++;
                found = 1;
                break;
            }
        }
        
        // If the word is new, add it to the list
        if (!found) {
            strcpy(words[word_count], token);
            count[word_count]++;
            word_count++;
        }
        
        token = strtok(NULL, " ");
    }
    
    // Construct the output string with unique words
    strcpy(output, "");
    for (int i = 0; i < word_count; i++) {
        strcat(output, words[i]);
        strcat(output, " ");
    }
    
    // Remove trailing space
    if (strlen(output) > 0) {
        output[strlen(output) - 1] = '\0';
    }
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char result[BUFFER_SIZE] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    // Accept a connection from a client
    if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Receive the message from the client
        memset(buffer, 0, BUFFER_SIZE);
        read(client_socket, buffer, BUFFER_SIZE);

        // Check for "stop" command
        if (strcmp(buffer, "stop") == 0) {
            printf("Received 'stop' command. Terminating server.\n");
            break;
        }

        printf("Received message: %s\n", buffer);

        // Remove duplicate words
        remove_duplicates(buffer, result);

        // Send the result back to the client
        send(client_socket, result, strlen(result), 0);

        printf("Processed message sent: %s\n", result);
    }

    // Close the connection
    close(client_socket);
    close(server_fd);

    return 0;
}
