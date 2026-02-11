#include "commands.hpp"
#include "alias_manager.hpp"
#include <iostream>

void handleAdd(
    AliasMap& aliases, const std::string& name, const std::string& cmd,
    const std::string& desc)
{
    aliases[name] = {cmd, desc};
    saveAliases(aliases);
}

void handleRemove(AliasMap& aliases, const std::string& name) {
    aliases.erase(name);
    saveAliases(aliases);
}

void handleChange(
    AliasMap& aliases, const std::string& oldName, const std::string& newName,
    const std::string& cmd, const std::string& desc)
{
    auto& a = aliases[oldName];

    if (!newName.empty()) {
        aliases[newName] = a;
        aliases.erase(oldName);
    }
    if (!cmd.empty())
        a.command = cmd;
    if (!desc.empty())
        a.description = desc;

    saveAliases(aliases);
}

void handleInspect(const AliasMap& aliases, const std::string& name, bool showCmd, bool showDesc) {
    if (showCmd && !showDesc) {
        std::cout << aliases.at(name).command << std::endl;
    }
    else if (!showCmd && showDesc) {
        std::cout << aliases.at(name).description << std::endl;
    }
    else {
        std::cout << "Alias: " << name << "\nCommand: " << aliases.at(name).command 
            << "\nDescription: " << aliases.at(name).description << std::endl;
    }
}

void handleList(const AliasMap& aliases) {
    for (const auto& a : aliases) {
        std::cout << a.first << std::endl;
    }
}

void handleVersion(const std::string& version) {
    std::cout << "PowerShell-Aliases v" << version << std::endl;
}
