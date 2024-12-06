#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_BUF_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    int arr_size;
    int *arr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    printf("Enter the number of elements in the array: ");
    scanf("%d", &arr_size);

    arr = (int *)malloc(arr_size * sizeof(int));
    if (!arr) {
        perror("Memory allocation failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Enter the elements of the array: ");
    for (int i = 0; i < arr_size; i++) {
        scanf("%d", &arr[i]);
    }

    if (send(sock, &arr_size, sizeof(arr_size), 0) <= 0) {
        perror("Failed to send array size");
        free(arr);
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (send(sock, arr, arr_size * sizeof(int), 0) <= 0) {
        perror("Failed to send array elements");
        free(arr);
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (recv(sock, arr, arr_size * sizeof(int), 0) <= 0) {
        perror("Failed to receive sorted array");
        free(arr);
        close(sock);
        exit(EXIT_FAILURE);
    }

    int pid;
    if (recv(sock, &pid, sizeof(pid), 0) <= 0) {
        perror("Failed to receive process ID");
        free(arr);
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Sorted Array: ");
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nServer Process ID: %d\n", pid);

    free(arr);
    close(sock);
    return 0;
}
