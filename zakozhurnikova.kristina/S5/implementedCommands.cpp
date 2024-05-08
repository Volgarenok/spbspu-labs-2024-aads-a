#include <iostream>
#include <scopeGuard.hpp>
#include "getSum.hpp"
#include "implementedCommands.hpp"

namespace zak = zakozhurnikova;
using map = zak::BinarySearchTree< long long, std::string >;

zak::ImplementedCommands::ImplementedCommands(BinarySearchTree< long long, std::string >& map):
  map_(map)
{
  commands_.push("ascending", &ImplementedCommands::ascending);
  commands_.push("descending", &ImplementedCommands::descending);
  commands_.push("breadth", &ImplementedCommands::breadth);
}

long long zak::ImplementedCommands::executeCommand(std::string& command, std::string& result)
{
  long long sum = 0;
  sum = (this->*commands_.at(command))(result);
  return sum;
}

long long zak::ImplementedCommands::ascending(std::string& result)
{
  KeySum amount;
  map_.traverse_lnr(amount, result);
  long long sum = amount.result_;
  return sum;
}

long long zak::ImplementedCommands::descending(std::string& result)
{
  KeySum amount;
  map_.traverse_rnl(amount, result);
  long long sum = amount.result_;
  return sum;
}

long long zak::ImplementedCommands::breadth(std::string& result)
{
  KeySum amount;
  map_.traverse_breadth(amount, result);
  long long sum = amount.result_;
  return sum;
}
