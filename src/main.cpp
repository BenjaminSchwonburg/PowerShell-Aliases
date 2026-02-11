#include "CLI11.hpp"
#include "alias_manager.hpp"
#include "commands.hpp"
#include <string>

int main(int argc, char** argv) {

    const std::string VERSION = "1.0.0";

    CLI::App app{"PowerShell-Aliases"};
    argv = app.ensure_utf8(argv);

    app.require_subcommand(0,1);

    auto cmdAdd = app.add_subcommand("add", "Add a new alias");
    auto cmdRemove = app.add_subcommand("remove", "remove an alias");
    auto cmdChange = app.add_subcommand("change", "change the alias, command or description of an alias");
    auto cmdInspect = app.add_subcommand("inspect", "inspect the command behind an alias");
    auto cmdList = app.add_subcommand("list", "list all aliases");
    auto cmdVersion = app.add_subcommand("version", "show the version of PowerShell-Aliases");

    std::string aliasToRun;
    std::string argAlias;
    std::string argCommand;
    std::string argDescription;
    std::string argNewAlias;
    bool showCommand;
    bool showDescription;

    app.add_option("aliasToRun", aliasToRun, "run command of an alias");

    cmdAdd->add_option("aliasToAdd", argAlias, "name of the alias to be created")->required();
    cmdAdd->add_option("command", argCommand, "command behind the alias")->required();
    cmdAdd->add_option("-d,--description", argDescription, "description for the alias");

    cmdRemove->add_option("aliasToRemove", argAlias, "name of the alias to be removed")->required();

    cmdChange->require_option(1);
    cmdChange->add_option("aliasToChange", argAlias, "name of the command to be changed")->required();
    cmdChange->add_option("-a,--alias", argNewAlias, "change the name of the alias");
    cmdChange->add_option("-c,--command", argCommand, "change the command of the alias");
    cmdChange->add_option("-d,--description", argDescription, "change the description of the alias");

    cmdInspect->add_option("aliasToInspect", argAlias, "alias to be inspected")->required();
    cmdInspect->add_flag("-c,--command", showCommand, "show just the command of an alias");
    cmdInspect->add_flag("-d,--description", showDescription, "show just the description of an alias");

    std::unordered_map<std::string, Alias> aliases;

    loadAliases(aliases);

    app.callback([&]() {
        if (!aliasToRun.empty()) {
            auto it = aliases.find(aliasToRun);
            if (it != aliases.end()) {
                std::string fullCommand =
                "powershell -NoProfile -Command \"" + it->second.command + "\"";
                system(fullCommand.c_str());
            }
        }
    });

    cmdAdd->callback([&]() {
        handleAdd(aliases, argAlias, argCommand, argDescription);
    });

    cmdRemove->callback([&]() {
        handleRemove(aliases, argAlias);
    });

    cmdChange->callback([&]() {
        handleChange(aliases, argAlias, argNewAlias, argCommand, argDescription);
    });

    cmdInspect->callback([&]() {
        handleInspect(aliases, argAlias, showCommand, showDescription);
    });

    cmdList->callback([&]() {
        handleList(aliases);
    });

    cmdVersion->callback([&]() {
        handleVersion(VERSION);
    });

    CLI11_PARSE(app, argc, argv);
    return 0;

}
