/*
12.8 Demonstrate skill in handling partial send()/recv()
Objectives
- N/A
*/
#include "common.h"

void run_server(SocketFD s_sock);
SocketFD setup_socket();

int32_t main(int32_t argc, char** argv)
{
    SockAddressIn s_address;
    SocketFD s_sock = setup_socket(&s_address);

    run_server(s_sock);

    close(s_sock);

    return EXIT_SUCCESS;
}

SocketFD setup_socket(SockAddressIn* out)
{
    SocketFD s = 0;

    out->sin_family = AF_INET;
    out->sin_port = htons(DEFAULT_SERVER_PORT);
    out->sin_addr.s_addr = htonl(INADDR_ANY);

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (bind(s, (struct sockaddr*)out, sizeof(*out)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(s, MAX_CONNECTIONS) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return s;
}

void run_server(SocketFD s)
{
    SocketFD c;
    SockAddressIn c_address;
    socklen_t c_address_length;

    Message c_message =
    {
        .id = 0,
        .data_length = 0,
        .data = NULL
    };

    bool is_header_read = false;
    ssize_t bytes_recv;
    char* recv_buffer = (char*)calloc(MAX_RECV_BUFFER, sizeof(char));
    char* buff_ptr = recv_buffer;
    char* data_ptr = NULL;
    size_t copy_count = 0;

    for (;;)
    {
        if ((c = accept(s, (struct sockaddr *)&c_address, &c_address_length)) < 0)
            continue;

        if(getpeername(c, (struct sockaddr *)&c_address, &c_address_length) == 0)
            printf("Connection from: %s:%d\n", inet_ntoa(c_address.sin_addr), ntohs(c_address.sin_port));
        else
            printf("WARNING: Unrecognized connection from client socket %d\n", c);

        while((bytes_recv = recv(c, recv_buffer, MAX_RECV_BUFFER, 0)) > 0)
        {
            buff_ptr = recv_buffer;
            copy_count = 0;

            if(is_header_read == false)
            {
                is_header_read = true;
                c_message.id = *buff_ptr++;
                c_message.data_length = *buff_ptr++;
                // Allocate 1 additional char for null byte.
                c_message.data = (char*)calloc(c_message.data_length + 1, sizeof(char));
                data_ptr = c_message.data;
            }

            while (*buff_ptr != '\0' && copy_count != c_message.data_length)
            {
                *data_ptr = *buff_ptr++;
                data_ptr++;
                copy_count++;
            }

            memset(recv_buffer, 0, MAX_RECV_BUFFER);
        }

        // Print the message to standard out
        handle_message(&c_message, &c_address);
        // Reuse the message struct for the next message.
        reset_message(&c_message);

        is_header_read = false;
        close(c);
    }

    free(recv_buffer);   
}