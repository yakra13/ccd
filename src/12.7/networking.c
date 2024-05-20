/*
12.7 In C, demonstrate skill in using networking commands accounting for endianness
Objectives

- [ ] struct sockaddr_un
- [ ] struct sockaddr_storage
- [12.8] socket()
- [ ] gethostname()
- [12.8] send()
- [12.8] recv()
- [ ] sendto()
- [ ] recvfrom()
- [12.8] bind()
- [12.8] connect()
- [12.8] accept()
- [ ] getsockopt()
- [ ] setsockopt()
- [ ] getaddrinfo()
- [12.8] struct sockaddr
- [12.8] struct sockaddr_in
*/
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


#define DEFAULT_SERVER_PORT 7777
#define MAX_CONNECTIONS 1
#define MAX_RECV_BUFFER 16
#define MAX_SEND_BUFFER 32

typedef int SocketFD;
typedef struct sockaddr_in SockAddressIn;

int32_t main(int32_t argc, char** argv)
{
    struct sockaddr_un unix_address;
    struct sockaddr_storage storage;
    
    struct addrinfo hints, *info, *p;
    int32_t gai_result;
    char hostname[1024] = {'\0'};
    gethostname(hostname, 1023);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // ipv4 or ipv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    if ((gai_result = getaddrinfo(hostname, "http", &hints, &info)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_result));
        exit(EXIT_FAILURE);
    }

    for(p = info; p != NULL; p = p->ai_next)
    {
        printf("hostname: %s\n", p->ai_canonname);
    }


    return EXIT_SUCCESS;
}