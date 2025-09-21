#include <iostream>

#include "lib/ssh.h"
#include "lib/error.h"

int main(void)
{
    SSH ssh;
    try
    {
        ssh.connect();
    }
    catch (const VPSError &err)
    {
        std::cerr << err.what() << std::endl;
        if (!err.more().empty())
            std::cerr << "Reason: " << err.more() << std::endl;
        return err.code();
    }

    std::cout << "Connection success!" << std::endl;
    ssh.send_cmd("systemctl is-active craft2exile");
    std::cout << "ssh: " << ssh.get_stdout() << std::endl;
    ssh.send_cmd("systemctl is-active atm10");
    std::cout << "ssh: " << ssh.get_stdout() << std::endl;
    return 0;
}
