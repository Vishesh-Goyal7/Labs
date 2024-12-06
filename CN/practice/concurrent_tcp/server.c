#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

void sorter(int* arr, int arr_size){
    for(int i = 0; i < arr_size - 1; i++){
        for(int j = 0; j < arr_size - i - 1; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){

    int *arr, arr_size;
    int server_fd;
    struct sockaddr_in 
}