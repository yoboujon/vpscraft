#include <iostream>
#include <thread>
#include <chrono>

#include "lib/vpscraft.h"
#include "lib/error.h"

int main(void)
{
    VPSCraft vps;
    try
    {
        vps.init("mc.etheryo.fr", "root");
    }
    catch (const VPSError &err)
    {
        std::cerr << err.what() << std::endl;
        if (!err.more().empty())
            std::cerr << "Reason: " << err.more() << std::endl;
        return err.code();
    }

    auto list = vps.get_active_list();
    for (const auto &l : list)
        std::cout << l.first << ": " << (l.second ? "on" : "off") << std::endl;

    if (vps.get_active("craft2exile") == false)
    {
        vps.set_instance("craft2exile", true);
        bool active = false;
        while (!active)
        {
            active = vps.get_active("craft2exile");
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        std::cout << "craft2exile started!" << std::endl;
    }
    return 0;
}
