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

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Take array size input
    printf("Enter the number of elements in the array: ");
    scanf("%d", &arr_size);

    int arr[arr_size];
    
    // Take array elements input
    printf("Enter the elements of the array: ");
    for (int i = 0; i < arr_size; i++) {
        scanf("%d", &arr[i]);
    }

    // Send the array size to the server
    send(sock, &arr_size, sizeof(arr_size), 0);

    // Send the array to the server
    send(sock, arr, arr_size * sizeof(int), 0);

    // Receive the sorted array from the server
    recv(sock, arr, arr_size * sizeof(int), 0);

    // Receive the process ID of the server
    int pid;
    recv(sock, &pid, sizeof(pid), 0);

    // Display the sorted array and process ID
    printf("Sorted Array: ");
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nServer Process ID: %d\n", pid);

    close(sock);
    return 0;
}
