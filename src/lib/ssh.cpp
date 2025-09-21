#include "lib/ssh.h"
#include "lib/error.h"

#include "libssh/libssh.h"

#include <string>

static int PORT = 22;

void connect_ssh()
{
    std::string reason;
    ssh_session session = ssh_new();
    if (session == NULL)
        throw VPSError(VPSErrorEnum::SSH_SESSION_FAIL);

    ssh_options_set(session, SSH_OPTIONS_HOST, "mc.etheryo.fr");
    ssh_options_set(session, SSH_OPTIONS_USER, "root");
    ssh_options_set(session, SSH_OPTIONS_PORT, &PORT);
    if (ssh_connect(session) != SSH_OK)
    {
        reason = ssh_get_error(session);
        ssh_free(session);
        throw VPSError(VPSErrorEnum::SSH_CONNECTION_FAIL, reason);
    }

    if (ssh_userauth_publickey_auto(session, NULL, NULL) != SSH_AUTH_SUCCESS)
    {
        reason = ssh_get_error(session);
        ssh_disconnect(session);
        ssh_free(session);
        throw VPSError(VPSErrorEnum::SSH_AUTH_FAIL, reason);
    }
}

/*
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    ssh_session session = ssh_new();
    if (session == NULL) return -1;

    // --- Connection setup ---
    ssh_options_set(session, SSH_OPTIONS_HOST, "my.server.com");
    ssh_options_set(session, SSH_OPTIONS_USER, "myuser");
    ssh_options_set(session, SSH_OPTIONS_PORT, &(int){22});

    if (ssh_connect(session) != SSH_OK) {
        fprintf(stderr, "Error connecting: %s\n", ssh_get_error(session));
        ssh_free(session);
        return -1;
    }

    // --- Authenticate with keys ---
    if (ssh_userauth_publickey_auto(session, NULL, NULL) != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Auth failed: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        return -1;
    }

    // --- Run a command remotely ---
    ssh_channel channel = ssh_channel_new(session);
    ssh_channel_open_session(channel);
    ssh_channel_request_exec(channel,
        "echo 'say Hello from libssh' > /var/run/minecraft.stdin");

    ssh_channel_close(channel);
    ssh_channel_free(channel);

    ssh_disconnect(session);
    ssh_free(session);

    return 0;
}

*/