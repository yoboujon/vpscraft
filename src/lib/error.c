#include "lib/error.h"

#include <string.h>

static const char *errors[] = {
    "RCON Port is unreachable",
    "Wrong Password",
    "RCON Packet is ill-formed."
};

const char* rcon_error_str(int error)
{
    return errors[error-1];
}
