#ifndef VPSCRAFT_SOCKET
#define VPSCRAFT_SOCKET

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void tcp_init(const char *ip, uint16_t port);
void tcp_send(void* data, size_t size);
void* tcp_receive(size_t* size);
void tcp_clean();

#ifdef __cplusplus
}
#endif


#endif // VPSCRAFT_SOCKET
