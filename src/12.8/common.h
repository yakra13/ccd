#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "message.h"

#define DEFAULT_SERVER_PORT 7777
#define MAX_CONNECTIONS 1
#define MAX_RECV_BUFFER 16
#define MAX_SEND_BUFFER 32

typedef int SocketFD;
typedef struct sockaddr_in SockAddressIn;