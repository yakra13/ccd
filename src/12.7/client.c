/*
12.7 In C, demonstrate skill in using networking commands accounting for endianness
Objectives

- [ ] struct sockaddr_un
- [ ] struct sockaddr_storage
- [12.8] socket()
- [x] gethostname()
- [12.8] send()
- [12.8] recv()
- [x] sendto()
- [x] recvfrom()
- [12.8] bind()
- [12.8] connect()
- [12.8] accept()
- [x] getsockopt()
- [x] setsockopt()
- [x] getaddrinfo()
- [12.8] struct sockaddr
- [12.8] struct sockaddr_in
*/
#include "common.h"

int32_t main(int32_t argc, char** argv)
{
    if (argc != 2)
    {
        printf("USAGE: ./client \"message\"\n");
        exit(EXIT_SUCCESS);
    }

    size_t message_len = strlen(argv[1]);

    if(message_len > MAX_SEND_BUFFER)
    {
        printf("Message is too long.\n");
        exit(EXIT_SUCCESS);
    }

    SocketFD c;
    SockAddressIn server_address;
    char buffer[MAX_SEND_BUFFER] = {'\0'};
    socklen_t server_len;

    if ((c = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(DEFAULT_SERVER_ADDRESS);
    server_address.sin_port = htons(DEFAULT_SERVER_PORT);

    server_len = sizeof(server_address);

    if (sendto(c, argv[1], message_len, 0, (struct sockaddr *)&server_address, server_len) < 0)
    {
        perror("sendto");
        close(c);
        exit(EXIT_FAILURE);
    }

    if(recvfrom(c, buffer, MAX_RECV_BUFFER, 0, NULL, NULL) < 0)
    {
        perror("recvfrom");
        close(c);
        exit(EXIT_FAILURE);
    }

    printf(">> %s\n", buffer);

    close(c);

    return EXIT_SUCCESS;
}