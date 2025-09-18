#include <iostream>

#include "lib/rcon.h"
#include "lib/error.h"

int main(void)
{
    int error;
    if((error = rcon_connect("192.168.231.130", "1234")) != 0)
        std::cerr << rcon_error_str(error) << std::endl;
    std::cout << "Connection successful!" << std::endl;
    rcon_send_cmd("say hello");

    rcon_stop();
    return 0;
}
