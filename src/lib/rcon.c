#include "lib/rcon.h"
#include "lib/socket.h"
#include "lib/error.h"

#include <string.h>
#include <stdio.h>

#define DEFAULT_PORT 25575

typedef enum
{
    MULTIPACKET = 0,
    CMD = 2,
    LOGIN = 3
} rcon_type;

typedef struct
{
    int32_t length;
    int32_t request_id;
    int32_t type;
} __attribute__((__packed__)) rcon_header;

typedef struct
{
    rcon_header header;
    const char *msg;
} rcon_packet;

static uint8_t _packet[1024];
static int32_t _request_id;

static inline size_t create_rcon(void *payload, size_t size, rcon_type type)
{
    rcon_header p;
    char endline = '\0';
    p.length = size + sizeof(rcon_header) - 4 + 1;
    p.request_id = _request_id++;
    p.type = (int32_t)(type);
    memcpy(_packet, &p, sizeof(rcon_header));
    memcpy(_packet + sizeof(rcon_header), payload, size);
    memcpy(_packet + sizeof(rcon_header)+size, &endline, 1);
    return size + sizeof(rcon_header) + 1;
}

static inline rcon_packet cast_rcon(void *payload)
{
    rcon_header p;
    memcpy(&p, payload, sizeof(rcon_header));
    return (rcon_packet){p, payload + sizeof(rcon_header)};
}

static inline void print_rcon(void* payload)
{
    rcon_packet rp = cast_rcon(payload);
    printf("Len: %d\t\tRequest ID: %d\t\tType: %d\nMsg: %s\n", rp.header.length, rp.header.request_id, rp.header.type, rp.msg);
}

int rcon_connect(const char *ip, const char *password)
{
    tcp_init(ip, DEFAULT_PORT);
    size_t s = create_rcon((void *)password, strlen(password), LOGIN);
    tcp_send(_packet, s);

    size_t r_s = 0;
    void* data = tcp_receive(&r_s);
    if(r_s == 0)
        return ILL_FORMED_PACKET;
    rcon_packet rp = cast_rcon(data);
    if(rp.header.request_id != _request_id-1)
        return WRONG_PASSWORD;
    return 0;
}

void rcon_send_cmd(const char* cmd)
{
    size_t s = create_rcon((void *)cmd, strlen(cmd), CMD);
    tcp_send(_packet, s);
}

void rcon_stop()
{
    tcp_clean();
}
