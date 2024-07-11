/*
12.8 Demonstrate skill in handling partial send()/recv()
Objectives
- N/A
*/
#include <errno.h>
#include "common.h"

void message_to_buffer(char* buffer, Message* message);

int32_t main(int32_t argc, char** argv)
{
    if (argc > 2)
    {
        printf("USAGE: ./sendrecv_client \"message\"\n");
        exit(EXIT_FAILURE);
    }

    size_t input_length = strlen(argv[1]);
    if (input_length > 255)
    {
        printf("Input data too large. Max length is 255.\n");
        exit(EXIT_FAILURE);
    }

    int32_t c_sock = 0;
    int32_t conn = 0;

    struct sockaddr_in server_addr =
    {
        .sin_family = AF_INET,
        .sin_port = htons(DEFAULT_SERVER_PORT),
        .sin_addr.s_addr = 0
    };
    
    if((c_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error creating socket\n");
        exit(EXIT_FAILURE);
    }

    if ((conn = connect(c_sock, (struct sockaddr *) &server_addr, sizeof(server_addr))) < 0)
    {
        printf("Error connecting to server\n");
        exit(EXIT_FAILURE);
    }

    Message message =
    {
        .id = MESSAGE_STDOUT,
        .data_length = (uint8_t)input_length,
        .data = argv[1]
    };

    char* data_buffer = (char*)calloc(MESSAGE_HEADER_SIZE + message.data_length, sizeof(char));
    message_to_buffer(data_buffer, &message);

    size_t total_sent = 0;
    ssize_t remaining = (ssize_t)message.data_length + MESSAGE_HEADER_SIZE;
    int32_t attempts = 0;
    ssize_t bytes_sent = 0;

    while(remaining > 0)
    {
        bytes_sent = 0;
        errno = 0;
        if ((bytes_sent = send(c_sock, 
                data_buffer + total_sent,
                remaining > MAX_SEND_BUFFER ? MAX_SEND_BUFFER : remaining, 0)) > 0)
        {
            total_sent += bytes_sent;
            remaining -= bytes_sent;
        }
        else
        {
            if (errno == EINTR || bytes_sent == 0)
            {
                if (++attempts > 10)
                {
                    printf("send() attempts too high\n");
                    break;
                }

                continue;
            }
            else
            {
                printf("send() error: %s\n", strerror(errno));
                break;
            }
        }
    }

    close(conn);
    close(c_sock);
    free(data_buffer);

    return EXIT_SUCCESS;
}