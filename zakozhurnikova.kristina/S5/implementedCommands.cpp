#include <iostream>
#include <scopeGuard.hpp>
#include "implementedCommands.hpp"

namespace zak = zakozhurnikova;
using map = zak::BinarySearchTree< int, std::string >;

zak::ImplementedCommands::ImplementedCommands(BinarySearchTree< int, std::string > map):
  map_(map)
{
  commands_.push("ascending", &ImplementedCommands::ascending);
  commands_.push("descending", &ImplementedCommands::descending);
  commands_.push("breadth", &ImplementedCommands::breadth);
}

void zak::ImplementedCommands::executeCommand(std::string& command, std::string& result)
{
  if (command.empty())
  {
    result = std::string();
    return;
  }

  try
  {
    (this->*commands_.at(command))(result);
  }
  catch (const std::out_of_range& e)
  {
    throw std::invalid_argument("invalid command name");
  }
}
