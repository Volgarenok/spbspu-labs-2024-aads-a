#include "implementedCommands.hpp"
#include <iostream>
#include <scopeGuard.hpp>

namespace zak = zakozhurnikova;
using map = zak::BinarySearchTree< int, std::string >;

zak::ImplementedCommands::ImplementedCommands(BinarySearchTree< std::string, map >& maps):
  maps_(maps)
{}
void zak::ImplementedCommands::executeCommand(std::istream& input, std::string& result)
{
  ScopeGuard guard(input);
  input >> std::noskipws;
  List< std::string > args;
  std::string tmp;
  char delim = 0;

  while (input && delim != '\n')
  {
    input >> tmp;
    if (input)
    {
      args.push_back(tmp);
    }
    input >> delim;
  }

  if (args.empty())
  {
    result = std::string();
    return;
  }

  std::string cmdName = args.front();
  args.pop_front();
  try
  {
    (*commands_.at(cmdName))(args, result, maps_);
  }
  catch (const std::out_of_range& e)
  {
    try
    {
      (*printCmd_.at(cmdName))(args, result, maps_);
    }
    catch (const std::out_of_range&)
    {
      throw std::invalid_argument("invalid command name");
    }
  }
}

void zak::ImplementedCommands::addCommand(const std::string& nameCommand, Command command)
{
  commands_.push(nameCommand, command);
}

void zak::ImplementedCommands::addCommand(const std::string& nameCommand, PrintCmd command)
{
  printCmd_.push(nameCommand, command);
}
