#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080
#define MAX_BUF_SIZE 1024

// Function to sort the array
void sort_array(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Thread function to handle client communication
void *client_handler(void *client_sock) {
    int sock = *(int *)client_sock;
    int arr_size;
    
    // Receive the array size from the client
    recv(sock, &arr_size, sizeof(arr_size), 0);
    
    // Receive the array elements from the client
    int arr[arr_size];
    recv(sock, arr, arr_size * sizeof(int), 0);
    
    // Sort the array
    sort_array(arr, arr_size);
    
    // Send the sorted array and the server's process ID back to the client
    send(sock, arr, arr_size * sizeof(int), 0);
    int pid = getpid();
    send(sock, &pid, sizeof(pid), 0);
    
    close(sock);
    return NULL;
}

int main() {
    int server_fd, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    pthread_t tid;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept incoming connections
    addr_size = sizeof(client_addr);
    while (1) {
        new_sock = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
        if (new_sock < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected.\n");

        // Create a new thread to handle the client
        if (pthread_create(&tid, NULL, client_handler, (void *)&new_sock) != 0) {
            perror("Thread creation failed");
        }
    }

    close(server_fd);
    return 0;
}
