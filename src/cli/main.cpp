#include <iostream>

#include "lib/ssh.h"
#include "lib/error.h"

int main(void)
{
    try
    {
        connect_ssh();
    }
    catch (const VPSError &err)
    {
        std::cerr << err.what() << std::endl;
        if (!err.more().empty())
            std::cerr << "Reason: " << err.more() << std::endl;
        return err.code();
    }

    std::cout << "Connection success!" << std::endl;
    return 0;
}
