#include "lib/vpscraft.h"
#include "lib/error.h"

// Will be changed by the config file
static std::vector<std::string> instances =
    {
        "craft2exile",
        "atm10"};

VPSCraft::VPSCraft()
{
}

void VPSCraft::init(const char *host, const char *user)
{
    _ssh.connect(host, user);
    _instances = instances;
    this->update();
}

void VPSCraft::update()
{
    for (const auto &i : _instances)
    {
        const std::string cmd = "systemctl is-active " + i;
        _ssh.send_cmd(cmd.c_str());
        _active[i] = (_ssh.get_stdout() == "active");
    }
}

bool VPSCraft::get_active(const std::string &str)
{
    this->update();
    return _active[str];
}

std::unordered_map<std::string, bool>& VPSCraft::get_active_list()
{
    this->update();
    return _active;
}
