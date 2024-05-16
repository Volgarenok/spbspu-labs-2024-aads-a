#include "implementedCommands.hpp"
#include <iostream>
#include <scopeGuard.hpp>
#include "getSum.hpp"

namespace zak = zakozhurnikova;
using map = zak::BinarySearchTree< int, std::string >;

zak::ImplementedCommands::ImplementedCommands(BinarySearchTree< int, std::string >& map):
  map_(map)
{}

int zak::ImplementedCommands::executeCommand(std::string& command, std::string& result)
{
  int sum = 0;
  sum = (*commands_.at(command))(result, map_);
  return sum;
}

void zak::ImplementedCommands::addCommand(const std::string& nameCommand, Command command)
{
  commands_.push(nameCommand, command);
}
