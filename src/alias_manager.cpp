#include "json.hpp"
#include "alias_manager.hpp"
#include <fstream>

using json = nlohmann::json;

void loadAliases(AliasMap& aliases, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    json j;
    file >> j;

    for (auto& [name, value] : j.items()) {
        aliases[name] = { value["command"].get<std::string>(), value.value("description","") };
    }
}

void saveAliases(const AliasMap& aliases, const std::string& filename) {
    json j;
    for (const auto& [name, a] : aliases) {
        j[name] = { {"command", a.command}, {"description", a.description} };
    }
    std::ofstream file(filename);
    file << j.dump(4);
}
