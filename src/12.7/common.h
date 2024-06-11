#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define DEFAULT_SERVER_ADDRESS "127.0.0.1"
#define DEFAULT_SERVER_PORT 7777
#define MAX_CONNECTIONS 1
#define MAX_RECV_BUFFER 4096
#define MAX_SEND_BUFFER 4096
#define SOCKET_PATH "example_socket"

typedef int SocketFD;
typedef struct sockaddr SockAddress;
typedef struct sockaddr_in SockAddressIn;
typedef struct sockaddr_in6 SockAddressIn6;
typedef struct sockaddr_un SockAddressUnix;
typedef struct addrinfo AddressInfo;
typedef struct sockaddr_storage AddressStorage;
