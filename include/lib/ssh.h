#ifndef VPSCRAFT_SSH
#define VPSCRAFT_SSH

#include "libssh/libssh.h"
#include <string>

class SSH {
public:
    SSH() noexcept;
    ~SSH() noexcept;
    void connect();
    void send_cmd(const char* cmd) noexcept;
    std::string& get_stdout() noexcept;
    std::string& get_stderr() noexcept;
private:
    int _port;
    ssh_session _session;
    ssh_channel _channel;
    std::string _stdout;
    std::string _stderr;
};

void connect_ssh();
void close_ssh();

#endif // VPSCRAFT_SSH