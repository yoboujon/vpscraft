#include "lib/error.h"

const char *_to_what(VPSErrorEnum error)
{
    if (error == VPSErrorEnum::SSH_SESSION_FAIL)
        return "SSH Session Failed";
    else if (error == VPSErrorEnum::SSH_CONNECTION_FAIL)
        return "Connection failed";
    else if (error == VPSErrorEnum::SSH_AUTH_FAIL)
        return "Authentication failed";
    else
        return "Unknown error";
}

VPSError::VPSError(VPSErrorEnum code, const std::string& arg)
    : std::exception(_to_what(code)), _code(static_cast<int>(code)), _more(arg)
{
}

int VPSError::code() const noexcept
{
    return _code;
}

const std::string& VPSError::more() const noexcept
{
    return _more;
}
