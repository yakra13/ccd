#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7777
#define MAX_BUFFER_SIZE 1024

typedef struct message
{
    uint16_t id;
    uint16_t message_length;
    uint8_t* message;
} Message;

int main()
{
    printf("Just a test.\n");
    int server_fd;
    struct sockaddr_in address;
    
    uint8_t buffer[MAX_BUFFER_SIZE];
    int bytes_received;
    
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    uint8_t* data = "Test data message."; 

    Message m = 
    {
        .id = 0xABCD,
        .message_length = sizeof(data),
        .message = data
    };

    while(true)
    {
        while((bytes_received = recv(server_fd, buffer, sizeof(buffer), 0)) > 0)
        {

        }
    }


    return 0;
}