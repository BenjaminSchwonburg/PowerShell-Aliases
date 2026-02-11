#include "CLI11.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {

    CLI::App app{"PowerShell-Aliases"};
    argv = app.ensure_utf8(argv);

    app.require_subcommand();

    auto cmdAdd = app.add_subcommand("add", "Add a new alias");
    auto cmdRemove = app.add_subcommand("remove", "remove an alias");
    auto cmdChange = app.add_subcommand("change", "change the alias, command or description of an alias");
    auto cmdInspect = app.add_subcommand("inspect", "inspect the command behind an alias");
    auto cmdList = app.add_subcommand("list", "list all aliases");
    auto cmdHelp = app.add_subcommand("help", "command to show help");

    std::string argAlias;
    std::string argCommand;
    std::string argDescription;
    std::string argNewAlias;

    cmdAdd->add_option("alias", argAlias, "name of the command to be created")->required();
    cmdAdd->add_option("command", argCommand, "command behind the alias")->required();
    cmdAdd->add_option("-d,--description", argDescription, "description for the alias");

    cmdRemove->add_option("alias", argAlias, "name of the command to be removed")->required();

    cmdChange->add_option("alias", argAlias, "name of the command to be changed")->required();
    cmdChange->add_option("-a,--alias", argNewAlias, "new alias for the command");
    cmdChange->add_option("-c,--command", argCommand, "new command for the alias");
    cmdChange->add_option("-d,--description", argDescription, "new description for the alias");

    cmdInspect->add_option("alias", argAlias, "alias to be inspected")->required();
    cmdInspect->add_option("-c,--command", argCommand, "show just command of an alias");
    cmdInspect->add_option("-d,--description", argDescription, "show just description of an alias");


    /*
    std::string filename = "default";
    app.add_option("-f,--file", filename, "A help string");
    */

    CLI11_PARSE(app, argc, argv);
    return 0;

}
