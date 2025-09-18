#include "lib/socket.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define START_WSA WSAStartup(MAKEWORD(2, 2), &_wsa);
#define STOP_WSA WSACleanup();
#define CLOSE_TCP(x) closesocket(x)
static WSADATA _wsa;
#else
#define START_WSA
#define STOP_WSA
#define CLOSE_TCP(x) close(x)
#endif

static int _sockfd;
static struct sockaddr_in _sock_addr;
static char* _buffer[1024];

void tcp_init(const char *ip, uint16_t port)
{
    START_WSA;
    if ((_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Could not create socket datagram");
        exit(EXIT_FAILURE);
    }

    _sock_addr.sin_family = AF_INET;
    _sock_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &_sock_addr.sin_addr) <= 0)
    {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    if (connect(_sockfd, (struct sockaddr *)(&_sock_addr), sizeof(_sock_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
}

void tcp_send(void *data, size_t size)
{
    send(_sockfd, data, size, 0);
}

void *tcp_receive(size_t* size)
{
    *size = recv(_sockfd, _buffer, 1024, 0);
    return _buffer;
}

void tcp_clean()
{
    CLOSE_TCP(_sockfd);
    STOP_WSA
}
