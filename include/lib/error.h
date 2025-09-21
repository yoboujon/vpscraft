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
    const char* what() const noexcept override;
    int code() const noexcept;
    const std::string& more() const noexcept;
private:
    std::string _what;
    std::string _more;
    int _code;
};

#endif // VPSCRAFT_ERROR
