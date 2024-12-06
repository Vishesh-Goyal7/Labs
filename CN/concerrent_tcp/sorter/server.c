#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_BUF_SIZE 1024

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

void *client_handler(void *client_sock_ptr) {
    int client_sock = *(int *)client_sock_ptr;
    free(client_sock_ptr);

    int arr_size;
    int *arr;

    if (recv(client_sock, &arr_size, sizeof(arr_size), 0) <= 0) {
        perror("Failed to receive array size");
        close(client_sock);
        return NULL;
    }

    arr = (int *)malloc(arr_size * sizeof(int));
    if (!arr) {
        perror("Memory allocation failed");
        close(client_sock);
        return NULL;
    }

    if (recv(client_sock, arr, arr_size * sizeof(int), 0) <= 0) {
        perror("Failed to receive array elements");
        free(arr);
        close(client_sock);
        return NULL;
    }

    sort_array(arr, arr_size);

    if (send(client_sock, arr, arr_size * sizeof(int), 0) <= 0) {
        perror("Failed to send sorted array");
    }

    int pid = getpid();
    if (send(client_sock, &pid, sizeof(pid), 0) <= 0) {
        perror("Failed to send process ID");
    }

    free(arr);
    close(client_sock);
    return NULL;
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    pthread_t thread_id;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    client_addr_len = sizeof(client_addr);
    while (1) {
        client_sock = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected.\n");
        int *client_sock_ptr = malloc(sizeof(int));
        if (!client_sock_ptr) {
            perror("Memory allocation failed");
            close(client_sock);
            continue;
        }
        *client_sock_ptr = client_sock;

        if (pthread_create(&thread_id, NULL, client_handler, (void *)client_sock_ptr) != 0) {
            perror("Thread creation failed");
            free(client_sock_ptr);
            close(client_sock);
        }

        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}
