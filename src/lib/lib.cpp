#include "lib/lib.h"
#include "libssh/libssh.h"

const char *print_lib()
{
    return "Hello from lib!";
}

int connect_ssh()
{
    ssh_session session = ssh_new();
    if (session == NULL)
        return -1;
    return 0;
}