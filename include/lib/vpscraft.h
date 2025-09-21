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
    bool get_active(const std::string& str);
    std::unordered_map<std::string, bool>& get_active_list();
    std::vector<std::string> get_instances();
private:
    SSH _ssh;
    std::vector<std::string> _instances;
    std::unordered_map<std::string, bool> _active;
};

#endif // VPSCRAFT