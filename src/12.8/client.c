#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "message.h"
#include "serverclient.h"

#define MAX_SEND_BUFFER 32
void message_to_buffer(char* buffer, Message* message);

int32_t main(int32_t argc, char** argv)
{
    printf("ARGS 0 : %s\n %s\n", argv[0], argv[1]);
    int client_sock = 0;
    int conn = 0;

    struct sockaddr_in server_addr =
    {
        .sin_family = AF_INET,
        .sin_port = htons(DEFAULT_SERVER_PORT), // next available port
        .sin_addr.s_addr = 0 // INADDR_ANY;
    };
    
    if((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)    //SOCK_STREAM for TCP
    {
        printf("Error creating socket\n");
        exit(EXIT_FAILURE);
    }

    if ((conn = connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr))) < 0)
    {
        printf("Error connecting to server\n");
        exit(1);
    }

    Message message =
    {
        .id = MESSAGE_STDOUT,
        .data_length = strlen(argv[1]),
        .data = argv[1]
    };

    printf("message len: %d\n", message.data_length);
    printf("message: %s\n", message.data);

    char* data_buffer = (char*)malloc((2 * sizeof(uint16_t)) + message.data_length * sizeof(char));

    message_to_buffer(data_buffer, &message);

    printf("message size: %lu\n", sizeof(data_buffer));
    printf("message buffer: %s\n", data_buffer + 4);
    size_t total_sent = 0;
    while(total_sent < (size_t)message.data_length + sizeof(uint16_t) + sizeof(uint8_t))
    {
        ssize_t s = 0;
        if ((s = send(client_sock, data_buffer + total_sent, MAX_SEND_BUFFER, 0)) > 0)
        {
            total_sent += s;
        }
    }

    close(client_sock);

    return EXIT_SUCCESS;
}

void message_to_buffer(char* buffer, Message* message)
{
    memcpy(buffer, &message->id, sizeof(uint16_t));
    memcpy(buffer + sizeof(uint16_t), &message->data_length, sizeof(uint16_t));
    strncpy(buffer + (2 * sizeof(uint16_t)), message->data, message->data_length);
    // memcpy(buffer + (2 * sizeof(uint16_t)) + message->data_length * sizeof(char), 
    //         message->data, message->data_length * sizeof(char));

    printf("dl: %d\n", message->data_length);

    for (int i = 0; i < message->data_length + 4; i++)
    {
        /* code */
        // fputc(*(message->data + i), stdout);
        fputc(*(buffer + i), stdout);
    }

    printf("\n");
    
}