#include "lib/ssh.h"
#include "lib/error.h"

#include <cstring>

#define BUFFER_SIZE 256
static int PORT = 22;
static char BUFFER[BUFFER_SIZE];

SSH::SSH() noexcept
    : _port(22), _session(nullptr), _channel(nullptr)
{
    std::memset(BUFFER, 0, BUFFER_SIZE);
}

SSH::~SSH() noexcept
{
    if (_channel != nullptr)
    {
        ssh_channel_send_eof(_channel);
        ssh_channel_close(_channel);
        ssh_channel_free(_channel);
    }
    if (_session != nullptr)
    {
        ssh_disconnect(_session);
        ssh_free(_session);
    }
}

void SSH::connect(const char *host, const char *user)
{
    std::string reason;
    _session = ssh_new();

    if (_session == NULL)
        throw VPSError(VPSErrorEnum::SSH_SESSION_FAIL);

    ssh_options_set(_session, SSH_OPTIONS_HOST, host);
    ssh_options_set(_session, SSH_OPTIONS_USER, user);
    ssh_options_set(_session, SSH_OPTIONS_PORT, &PORT);
    if (ssh_connect(_session) != SSH_OK)
    {
        reason = ssh_get_error(_session);
        throw VPSError(VPSErrorEnum::SSH_CONNECTION_FAIL, reason);
    }

    if (ssh_userauth_publickey_auto(_session, NULL, NULL) != SSH_AUTH_SUCCESS)
    {
        reason = ssh_get_error(_session);
        throw VPSError(VPSErrorEnum::SSH_AUTH_FAIL, reason);
    }

    // Just Checking if connection works
    _channel = ssh_channel_new(_session);
    if (ssh_channel_open_session(_channel) != SSH_OK)
    {
        reason = ssh_get_error(_session);
        throw VPSError(VPSErrorEnum::SSH_CHANNEL_FAIL, reason);
    }
    ssh_channel_send_eof(_channel);
    ssh_channel_close(_channel);
    ssh_channel_free(_channel);
    _channel = nullptr;
}

void SSH::send_cmd(const char *cmd) noexcept
{
    _stdout.clear();
    _stderr.clear();
    _channel = ssh_channel_new(_session);
    
    ssh_channel_open_session(_channel);
    ssh_channel_request_exec(_channel, cmd);
    int nbytes;
    while ((nbytes = ssh_channel_read(_channel, BUFFER, BUFFER_SIZE, 0)) > 0)
        _stdout.append(BUFFER);

    while ((nbytes = ssh_channel_read(_channel, BUFFER, BUFFER_SIZE, 1)) > 0)
        _stderr.append(BUFFER);

    // clearing the channel
    ssh_channel_send_eof(_channel);
    ssh_channel_close(_channel);
    ssh_channel_free(_channel);
    _channel = nullptr;
    std::memset(BUFFER, 0, BUFFER_SIZE);

    // removing last '\n'
    if (!_stdout.empty() && _stdout.back() == '\n')
        _stdout.pop_back();
    if (!_stderr.empty() && _stderr.back() == '\n')
        _stderr.pop_back();
}

std::string &SSH::get_stdout() noexcept
{
    return _stdout;
}

std::string &SSH::get_stderr() noexcept
{
    return _stderr;
}