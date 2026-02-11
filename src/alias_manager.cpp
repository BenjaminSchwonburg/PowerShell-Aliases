#include "json.hpp"
#include "alias_manager.hpp"
#include <fstream>
#include <windows.h>
#include <string>

using json = nlohmann::json;

std::string getExecutableDir();

void saveAliases(const std::unordered_map<std::string, Alias>& aliases) {
    std::string aliasFile = getExecutableDir() + "\\aliases.json";
    json j;
    for (const auto& [name, a] : aliases) {
        j[name] = { {"command", a.command}, {"description", a.description} };
    }
    std::ofstream file(aliasFile);
    file << j.dump(4);
}

void loadAliases(std::unordered_map<std::string, Alias>& aliases) {
    std::string aliasFile = getExecutableDir() + "\\aliases.json";
    std::ifstream file(aliasFile);
    if (!file.is_open()) return;

    json j;
    file >> j;

    for (auto& [name, value] : j.items()) {
        aliases[name] = {
            value["command"].get<std::string>(),
            value.value("description", "")
        };
    }
}

std::string getExecutableDir() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string fullPath(path);
    auto pos = fullPath.find_last_of("\\/");
    return fullPath.substr(0, pos);
}
