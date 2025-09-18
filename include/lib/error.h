#ifndef VPSCRAFT_ERROR
#define VPSCRAFT_ERROR

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    PORT_UNREACHABLE = 1,
    WRONG_PASSWORD,
    ILL_FORMED_PACKET,
} rcon_error;

const char* rcon_error_str(int error);

#ifdef __cplusplus
}
#endif

#endif // VPSCRAFT_ERROR
