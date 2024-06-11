/*
12.7 In C, demonstrate skill in using networking commands accounting for endianness
Objectives

- [x] struct sockaddr_un (SockAddressUnix)
- [x] struct sockaddr_storage (AddressStorage)
- [x] socket() (SocketFD)
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
- [x] struct sockaddr (SockAddress)
- [x] struct sockaddr_in (SockAddressIn)
*/
#include "common.h"

void print_addrinfo(char* hostname);
void print_hostname(char* host_buffer);
void print_socket_info(SocketFD s);
void print_storage(AddressStorage* addr);
void run_server(SocketFD s);
SocketFD setup_socket_UDP(SockAddressIn* out);
SocketFD setup_socket_unix(SockAddressUnix* out);

// NOTE: Development is done with WSL2 and unix sockets are not supported.
// As such the unix socket example is not implemented on the client side
// and setup_socket_unix() is merely meant to be a non-working example
// #define UNIX_EXAMPLE

int32_t main(int32_t argc, char** argv)
{
    SocketFD s;

#ifdef UNIX_EXAMPLE
    SockAddressUnix unix_addr;
    s = setup_socket_unix(&unix_addr);
#else
    SockAddressIn s_addr;
    s = setup_socket_UDP(&s_addr);
#endif

    char hostname[1024] = {'\0'};
    
    print_hostname(hostname);

    print_addrinfo(hostname);

    print_socket_info(s);

    run_server(s);

    close(s);

#ifdef UNIX_EXAMPLE
    unlink(SOCKET_PATH);
#endif

    return EXIT_SUCCESS;
}

// - [x] getaddrinfo()
void print_addrinfo(char* hostname)
{
    AddressInfo hints;
    AddressInfo *info;
    int32_t gai_result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // ipv4 or ipv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    if ((gai_result = getaddrinfo(hostname, NULL, &hints, &info)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_result));
        exit(EXIT_FAILURE);
    }

    char ipstr[INET6_ADDRSTRLEN];
    void* addr;
    char* ip_version;

    AddressInfo* ptr_info = info;
    if (ptr_info->ai_family == AF_INET)
    {
        SockAddressIn* ipv4 = (SockAddressIn*)ptr_info->ai_addr;
        addr = &(ipv4->sin_addr);
        ip_version = "IPv4";
    }
    else
    {
        SockAddressIn6* ipv6 = (SockAddressIn6*)ptr_info->ai_addr;
        addr = &(ipv6->sin6_addr);
        ip_version = "IPv6";
    }

    inet_ntop(ptr_info->ai_family, addr, ipstr, sizeof(ipstr));

    printf("  %s: %s\n", ip_version, ipstr);
    printf("  Family: %d\n", ptr_info->ai_family);
    printf("  Socket type: %d\n", ptr_info->ai_socktype);
    printf("  Protocol: %d\n", ptr_info->ai_protocol);
    printf("  Canonical name: %s\n", ptr_info->ai_canonname ? ptr_info->ai_canonname : "None");
    printf("  Address length: %d\n", ptr_info->ai_addrlen);

    freeaddrinfo(info);
}

// - [x] gethostname()
void print_hostname(char* host_buffer)
{
    gethostname(host_buffer, 1023);
    printf("Hostname: %s\n", host_buffer);
    printf("-------------------------------------------\n");
}

// - [x] getsockopt()
void print_socket_info(SocketFD s)
{
    int32_t v;
    socklen_t l = sizeof(v);
    int32_t opts[] =
    {
        SO_REUSEADDR,
        SO_KEEPALIVE,
        SO_SNDBUF,
        SO_RCVBUF
    };

    for (size_t i = 0; i < 4; i++)
    {
        int32_t res = getsockopt(s, SOL_SOCKET, opts[i], &v, &l);
        if (res < 0)
        {
            perror("getsockopt");
            exit(EXIT_FAILURE);
        }

        switch(opts[i])
        {
            case SO_REUSEADDR:
                printf("  SO_REUSEADDR: %s\n", (v ? "ON" : "OFF"));
                break;
            case SO_KEEPALIVE:
                printf("  SO_KEEPALIVE: %s\n", (v ? "ON" : "OFF"));
                break;
            case SO_SNDBUF:
                printf("  SO_SNDBUF: %d\n", v);
                break;
            case SO_RCVBUF:
                printf("  SO_RCVBUF: %d\n", v);
                break;
            default:
                break;
        }
    }
}

// - [x] struct sockaddr_storage (AddressStorage)
void print_storage(AddressStorage* addr)
{
    char ipstr[INET6_ADDRSTRLEN];

    if (addr->ss_family == AF_INET)
    {
        SockAddressIn *ipv4 = (SockAddressIn*)addr;
        inet_ntop(AF_INET, &ipv4->sin_addr, ipstr, sizeof(ipstr));
        printf("%s:", ipstr);
        printf("%d - ", ntohs(ipv4->sin_port));
    }
    else if (addr->ss_family == AF_INET6)
    {
        SockAddressIn6 *ipv6 = (SockAddressIn6*)addr;
        inet_ntop(AF_INET6, &ipv6->sin6_addr, ipstr, sizeof(ipstr));
        printf("%s:", ipstr);
        printf("%d - ", ntohs(ipv6->sin6_port));
    }
    else
    {
        printf("Unknown AF - ");
    }
}

// - [x] sendto()
// - [x] recvfrom()
void run_server(SocketFD s)
{
    AddressStorage c_addr;
    socklen_t c_len = sizeof(c_addr);

    char buffer[MAX_RECV_BUFFER] = {'\0'};

    for (;;)
    {
        if(recvfrom(s, buffer, MAX_RECV_BUFFER, 0, (SockAddress*)&c_addr, &c_len) < 0)
        {
            perror("recvfrom");
            return;
        }
        
        printf("<< ");
        print_storage(&c_addr);
        printf("%s\n", buffer);
        
        if (strlen(buffer) < MAX_RECV_BUFFER)
            strcat(buffer, "!");

        if (sendto(s, buffer, strlen(buffer), 0, (SockAddress*)&c_addr, c_len) < 0)
        {
            perror("sendto");
            return;
        }

        memset(buffer, 0, MAX_RECV_BUFFER);
    }
}

// - [x] struct sockaddr (SockAddress)
// - [x] struct sockaddr_in (SockAddressIn)
// - [x] socket() (SocketFD)
// - [x] setsockopt()
SocketFD setup_socket_UDP(SockAddressIn* out)
{
    SocketFD s = 0;

    out->sin_family = AF_INET;
    out->sin_port = htons(DEFAULT_SERVER_PORT);
    out->sin_addr.s_addr = INADDR_ANY;

    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (bind(s, (SockAddress*)out, sizeof(*out)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        perror("setsockopt SO_REUSEADDR");
        close(s);
        exit(EXIT_FAILURE);
    }

    if (setsockopt(s, SOL_SOCKET, SO_RCVBUF, &(int){MAX_RECV_BUFFER}, sizeof(int)) < 0)
    {
        perror("setsockopt SO_RCVBUF");
        close(s);
        exit(EXIT_FAILURE);
    }

        if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, &(int){MAX_SEND_BUFFER}, sizeof(int)) < 0)
    {
        perror("setsockopt SO_RCVBUF");
        close(s);
        exit(EXIT_FAILURE);
    }

#ifdef SO_REUSEPORT
    if (setsockopt(s, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0)
    { 
        perror("setsockopt SO_REUSEPORT");
        close(s);
        exit(EXIT_FAILURE);
    }
#endif

    return s;
}

SocketFD setup_socket_unix(SockAddressUnix* out)
{
    SocketFD s = 0;

    if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(out, 0, sizeof(SockAddressUnix));
    out->sun_family = AF_UNIX;
    strncpy(out->sun_path, SOCKET_PATH, sizeof(out->sun_path) - 1);

    unlink(SOCKET_PATH);

    // NOTE: Will fail here if running under WSL2 as Unix sockets are not supported.
    // This is meant only as an example of how to use struct sockaddr_un and is not
    // implemented in the client side for sending a message with a unix socket.
    if (bind(s, (SockAddress*)out, sizeof(SockAddressUnix)) < 0)
    {
        perror("bind");
        close(s);
        exit(EXIT_FAILURE);
    }

    printf("Unix socket waiting for connections...\n");

    return s;
}