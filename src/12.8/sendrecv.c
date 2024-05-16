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


#define MAX_BUFFER_SIZE 16 // 1024
#define MAX_CONNECTIONS 3

const char* test_data = "Test data message."; 
bool is_running = true;

int32_t main()
{
    printf("Just a test.\n");
    int server_sock = 0;
    int32_t client_sock = 0;
    struct sockaddr_in address =
    {
        .sin_family = AF_INET,
        .sin_port = htons(DEFAULT_SERVER_PORT),
        .sin_addr.s_addr = 0 //INADDR_ANY;
    };
    
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received;
    
    // int opt = 1;
    socklen_t addrlen = sizeof(address);

    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    // {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }

    if (bind(server_sock, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, MAX_CONNECTIONS) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    

    // Message m = 
    // {
    //     .id = 0xABCD,
    //     .data_length = sizeof(data),
    //     .data = test_data
    // };

    while(is_running)
    {
        if ((client_sock = accept(server_sock, (struct sockaddr*)&address, &addrlen)) > -1) 
        {
            bool first_packet = true;
            char* data_ptr = NULL;
            Message client_message = 
            {
                .id = 0,
                .data_length = 0,
                .data = NULL
            };
            printf("start receiving bytes\n");
            int16_t offset = 0;
            int32_t total_received = 0;

            while((bytes_received = recv(client_sock, buffer, sizeof(buffer), 0)) > 0)
            {
                total_received += bytes_received;
                char* buffer_ptr = buffer;
                printf("bytes recieved: %d\n", (int)bytes_received);
                // printf("contents: %s\n", buffer_ptr);

                if (first_packet)
                {
                    //extract id first 2 bytes of buffer
                    uint16_t tid = buffer[0]; //TODO verify this get the 0 index then inc then ptr

                    client_message.id = (uint16_t)((buffer_ptr[1] << 8) | buffer[0]);
                    //get the next 2 bytes
                    // uint8_t tlen = *buffer_ptr++;
                    client_message.data_length = (uint8_t)buffer_ptr[3];
                    printf("data length: %d\n", client_message.data_length);

                    client_message.data = (char*)calloc(client_message.data_length, sizeof(char));

                    data_ptr = client_message.data;
                    strncpy(client_message.data, buffer + 3, sizeof(buffer) - 3);

                    // bytes_received -= 4;
                    first_packet = false;
                    continue;
                }
                //write bytes to server stdout

                strncpy(client_message.data + total_received - 3, buffer, sizeof(buffer)));

                while (bytes_received-- > 0)
                {
                    *data_ptr = *buffer_ptr++;
                    data_ptr++;
                }
                printf("message so far: %s\n", client_message.data);
            }
            printf("Message:\n%s", client_message.data);

            switch (client_message.id)
            {
                case MESSAGE_STDOUT:
                    fputs(client_message.data, stdout);
                    break;
                
                default:
                    printf("Recieved invalid message id: %d\n", client_message.id);
                    is_running = false;
                    break;
            }

            free(client_message.data);
            close(client_sock);
        }

        
    }

    close(server_sock);

    return 0;
}