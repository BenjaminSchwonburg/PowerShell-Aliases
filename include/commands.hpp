#pragma once

#include "alias_manager.hpp"
#include <string>

void handleAdd(AliasMap& aliases, const std::string& name, const std::string& cmd, const std::string& desc);
void handleRemove(AliasMap& aliases, const std::string& name);
void handleChange(AliasMap& aliases, const std::string& oldName,
                  const std::string& newName, const std::string& cmd, const std::string& desc);
void handleInspect(const AliasMap& aliases, const std::string& name, bool showCmd, bool showDesc);
void handleList(const AliasMap& aliases);
void handleVersion(const std::string& version);
