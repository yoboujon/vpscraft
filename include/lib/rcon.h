#ifndef VPSCRAFT_RCON
#define VPSCRAFT_RCON

#ifdef __cplusplus
extern "C" {
#endif

int rcon_connect(const char* ip, const char* password);
void rcon_send_cmd(const char* cmd);
void rcon_stop();

#ifdef __cplusplus
}
#endif

#endif // VPSCRAFT_RCON
