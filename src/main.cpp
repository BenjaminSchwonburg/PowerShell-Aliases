#include "CLI11.hpp"
#include "json.hpp"
#include <string>
#include <fstream>

using json = nlohmann::json;

struct Alias {
    std::string command;
    std::string description;
};

void saveAliases(const std::unordered_map<std::string, Alias>& aliases);
void loadAliases(std::unordered_map<std::string, Alias>& aliases);

int main(int argc, char** argv) {

    CLI::App app{"PowerShell-Aliases"};
    argv = app.ensure_utf8(argv);

    app.require_subcommand(0,1);

    auto cmdAdd = app.add_subcommand("add", "Add a new alias");
    auto cmdRemove = app.add_subcommand("remove", "remove an alias");
    auto cmdChange = app.add_subcommand("change", "change the alias, command or description of an alias");
    auto cmdInspect = app.add_subcommand("inspect", "inspect the command behind an alias");
    auto cmdList = app.add_subcommand("list", "list all aliases");
    auto cmdHelp = app.add_subcommand("help", "show guide for the tool");

    std::string argAlias;
    std::string argCommand;
    std::string argDescription;
    std::string argNewAlias;
    bool showCommand;
    bool showDescription;

    app.add_option("alias", argAlias, "run command of an alias")->required();

    cmdAdd->add_option("alias", argAlias, "name of the command to be created")->required();
    cmdAdd->add_option("command", argCommand, "command behind the alias")->required();
    cmdAdd->add_option("-d,--description", argDescription, "description for the alias");

    cmdRemove->add_option("alias", argAlias, "name of the command to be removed")->required();

    cmdChange->add_option("alias", argAlias, "name of the command to be changed")->required();
    cmdChange->add_option("-a,--alias", argNewAlias, "new alias for the command");
    cmdChange->add_option("-c,--command", argCommand, "new command for the alias");
    cmdChange->add_option("-d,--description", argDescription, "new description for the alias");

    cmdInspect->add_option("alias", argAlias, "alias to be inspected")->required();
    cmdInspect->add_flag("-c,--command", showCommand, "show just command of an alias");
    cmdInspect->add_flag("-d,--description", showDescription, "show just description of an alias");

    std::unordered_map<std::string, Alias> aliases;

    loadAliases(aliases);

    app.callback([&]() {
        system(aliases[argAlias].command.c_str());
    });

    cmdAdd->callback([&]() {
        aliases[argAlias] = {argCommand, argDescription};
        saveAliases(aliases);
    });

    cmdRemove->callback([&]() {
        aliases.erase(argAlias);
        saveAliases(aliases);
    });

    cmdChange->callback([&]() {
        auto& a = aliases[argAlias];

        if (!argNewAlias.empty()) {
            aliases[argNewAlias] = a;
            aliases.erase(argAlias);
        }
        if (!argCommand.empty())
            a.command = argCommand;
        if (!argDescription.empty())
            a.description = argDescription;

        saveAliases(aliases);
    });


    CLI11_PARSE(app, argc, argv);
    return 0;

}

void saveAliases(const std::unordered_map<std::string, Alias>& aliases) {
    json j;

    for (const auto& [name, alias] : aliases) {
        j[name] = {
            {"command", alias.command},
            {"description", alias.description}
        };
    }

    std::ofstream file("aliases.json");
    file << j.dump(4);
}


void loadAliases(std::unordered_map<std::string, Alias>& aliases) {
    std::ifstream file("aliases.json");

    if (!file.is_open())
        return;

    json j;
    file >> j;

    for (auto& [name, value] : j.items()) {
        aliases[name] = {
            value["command"].get<std::string>(),
            value.value("description", "")
        };
    }
}
