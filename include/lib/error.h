#ifndef VPSCRAFT_ERROR
#define VPSCRAFT_ERROR

#include <exception>
#include <string>

enum class VPSErrorEnum : int
{
    SSH_SESSION_FAIL,
    SSH_CONNECTION_FAIL,
    SSH_AUTH_FAIL,
    SSH_CHANNEL_FAIL,
};

class VPSError : public std::exception
{
public:
    VPSError(VPSErrorEnum code, const std::string& arg="");
    int code() const noexcept;
    const std::string& more() const noexcept;
private:
    int _code;
    std::string _more;
};

#endif // VPSCRAFT_ERROR
