#include <iostream>
#include <scopeGuard.hpp>
#include "implementedCommands.hpp"
#include "getSum.hpp"

namespace zak = zakozhurnikova;
using map = zak::BinarySearchTree< int, std::string >;

zak::ImplementedCommands::ImplementedCommands(BinarySearchTree< int, std::string > map):
  map_(map)
{
  commands_.push("ascending", &ImplementedCommands::ascending);
//  commands_.push("descending", &ImplementedCommands::descending);
//  commands_.push("breadth", &ImplementedCommands::breadth);
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
  map_.traverse_lnr(amount);
  int sum = amount.result_;
  if (!map_.empty())
  {
    for (auto it = map_.cbegin(); it != map_.cend(); ++it)
    {
      result += it->second + ' ';
    }
    result.pop_back();
  }
  else
  {
    result = "<EMPTY>";
  }
  return sum;
}
