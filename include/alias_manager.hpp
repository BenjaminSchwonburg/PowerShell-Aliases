#pragma once
#include <string>
#include <unordered_map>

struct Alias {
    std::string command;
    std::string description;
};

using AliasMap = std::unordered_map<std::string, Alias>;

void loadAliases(AliasMap& aliases, const std::string& filename="aliases.json");
void saveAliases(const AliasMap& aliases, const std::string& filename="aliases.json");
