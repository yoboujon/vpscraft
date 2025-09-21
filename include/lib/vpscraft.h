#ifndef VPSCRAFT
#define VPSCRAFT

#include "lib/ssh.h"
#include <unordered_map>
#include <string>

class VPSCraft {
public:
    VPSCraft();
    void init(const char* host, const char* user);
    void update();
    bool get_active(const std::string& str, bool update=true);
    std::unordered_map<std::string, bool>& get_active_list();
    std::vector<std::string> get_instances();
    void set_instance(const std::string& instance, bool on);
private:
    SSH _ssh;
    std::vector<std::string> _instances;
    std::unordered_map<std::string, bool> _active;
};

#endif // VPSCRAFT