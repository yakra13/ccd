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

void print_addrinfo(char* hostname);
void print_hostname(char* host_buffer);
void print_socket_info(int32_t s);
void run_server(SocketFD s);
SocketFD setup_socket_UDP(SockAddressIn* out);

int32_t main(int32_t argc, char** argv)
{
    // TODO
    struct sockaddr_un unix_address;
    struct sockaddr_storage storage;

    SockAddressIn s_addr;
    SocketFD s = setup_socket_UDP(&s_addr);

    char hostname[1024] = {'\0'};
    
    print_hostname(hostname);

    print_addrinfo(hostname);

    print_socket_info(s);

    run_server(s);

    close(s);

    return EXIT_SUCCESS;
}

void print_addrinfo(char* hostname)
{
    AddressInfo hints;
    AddressInfo *info;
    int32_t gai_result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // ipv4 or ipv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    if ((gai_result = getaddrinfo(hostname, DEFAULT_SERVER_PORT, &hints, &info)) != 0)
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

void print_hostname(char* host_buffer)
{
    gethostname(host_buffer, 1023);
    printf("Hostname: %s\n", host_buffer);
    printf("-------------------------------------------\n");
}

void print_socket_info(int32_t s)
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

void run_server(SocketFD s)
{
    SockAddressIn c_addr;
    socklen_t c_len = sizeof(c_addr);

    char buffer[MAX_RECV_BUFFER] = {'\0'};

    for (;;)
    {
        if(recvfrom(s, buffer, MAX_RECV_BUFFER, 0, (struct sockaddr *)&c_addr, &c_len) < 0)
        {
            perror("recvfrom");
            return;
        }
        
        printf("<< %s\n", buffer);
        
        if (strlen(buffer) < MAX_RECV_BUFFER)
            strcat(buffer, "!");

        if (sendto(s, buffer, strlen(buffer), 0, (struct sockaddr *)&c_addr, c_len) < 0)
        {
            perror("sendto");
            return;
        }

        memset(buffer, 0, MAX_RECV_BUFFER);
    }
}

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

    if (bind(s, (struct sockaddr*)out, sizeof(*out)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        perror("setsockopt SO_REUSEADDR");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(s, SOL_SOCKET, SO_RCVBUF, &(int){MAX_RECV_BUFFER}, sizeof(int)) < 0)
    {
        perror("setsockopt SO_RCVBUF");
        exit(EXIT_FAILURE);
    }

        if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, &(int){MAX_SEND_BUFFER}, sizeof(int)) < 0)
    {
        perror("setsockopt SO_RCVBUF");
        exit(EXIT_FAILURE);
    }

#ifdef SO_REUSEPORT
    if (setsockopt(s, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0)
    { 
        perror("setsockopt SO_REUSEPORT");
        exit(EXIT_FAILURE);
    }
#endif

    return s;
}