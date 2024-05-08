#include <iostream>
#include <scopeGuard.hpp>
#include "implementedCommands.hpp"
#include "getSum.hpp"

namespace zak = zakozhurnikova;
using map = zak::BinarySearchTree< int, std::string >;

zak::ImplementedCommands::ImplementedCommands(BinarySearchTree< int, std::string >& map):
  map_(map)
{
  commands_.push("ascending", &ImplementedCommands::ascending);
  commands_.push("descending", &ImplementedCommands::descending);
  commands_.push("breadth", &ImplementedCommands::breadth);
}

int zak::ImplementedCommands::executeCommand(std::string& command, std::string& result)
{
  int sum = 0;
  try
  {
    sum = (this->*commands_.at(command))(result);
  }
  catch (const std::out_of_range& e)
  {
    throw std::invalid_argument("invalid command name");
  }
  return sum;
}

int zak::ImplementedCommands::ascending(std::string& result)
{
  KeySum amount;
  map_.traverse_lnr(amount, result);
  int sum = amount.result_;
  return sum;
}

int zak::ImplementedCommands::descending(std::string& result)
{
  KeySum amount;
  map_.traverse_lnr(amount, result);
  int sum = amount.result_;
  return sum;
}

int zak::ImplementedCommands::breadth(std::string& result)
{
  KeySum amount;
  map_.traverse_breadth(amount, result);
  int sum = amount.result_;
  return sum;
}
