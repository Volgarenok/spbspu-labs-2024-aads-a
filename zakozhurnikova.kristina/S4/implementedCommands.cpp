#include <iostream>
#include "implementedCommands.hpp"
#include "scopeGuard.hpp"

namespace zak = zakozhurnikova;
using map = zak::BinarySearchTree< int, std::string >;

zak::ImplementedCommands::ImplementedCommands(BinarySearchTree< std::string, map >& maps):
  maps_(maps)
{
  commands_.push("print", &ImplementedCommands::print);
  commands_.push("complement", &ImplementedCommands::complement);
  commands_.push("intersect", &ImplementedCommands::intersect);
  commands_.push("union", &ImplementedCommands::doUnion);
}
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

  try
  {
    std::string cmdName = args.front();
    args.pop_front();
    (this->*commands_.at(cmdName))(args, result);
  }
  catch (const std::out_of_range& e)
  {
    throw std::invalid_argument("invalid command name");
  }
}

void zak::ImplementedCommands::print(zak::List< std::string >& args, std::string& result)
{
  if (args.size() != 1)
  {
    throw std::invalid_argument("incorrect command source");
  }

  std::string mapName = args.back();
  if (!maps_.at(mapName).empty())
  {
    result = mapName + ' ';
    for (auto it = maps_[mapName].cbegin(); it != maps_[mapName].cend(); ++it)
    {
      result += std::to_string(it->first) + ' ';
      result += it->second + ' ';
    }
    result.pop_back();
  }
  else
  {
    result = "<EMPTY>";
  }
}

void zak::ImplementedCommands::complement(zak::List< std::string >& args, std::string& result)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  map& secondMap = maps_.at(args.back());
  args.pop_back();
  map& firstMap = maps_.at(args.back());
  map resultMap;

  for (auto it = firstMap.cbegin(); it != firstMap.cend(); ++it)
  {
    if (secondMap.find(it->first) == secondMap.cend())
    {
      resultMap.push(it->first, it->second);
    }
  }

  addMap(args.front(), resultMap);
  result = std::string();
}

void zak::ImplementedCommands::intersect(zak::List< std::string >& args, std::string& result)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  map& secondMap = maps_.at(args.back());
  args.pop_back();
  map& firstMap = maps_.at(args.back());
  map resultMap;

  for (auto it = firstMap.cbegin(); it != firstMap.cend(); ++it)
  {
    if (secondMap.find(it->first) != secondMap.cend())
    {
      resultMap.push(it->first, it->second);
    }
  }

  addMap(args.front(), resultMap);
  result = std::string();
}

void zak::ImplementedCommands::doUnion(List< std::string >& args, std::string& result)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  map& secondMap = maps_.at(args.back());
  args.pop_back();
  map& firstMap = maps_.at(args.back());
  map resultMap;

  for (auto it = firstMap.cbegin(); it != firstMap.cend(); ++it)
  {
    resultMap.push(it->first, it->second);
  }

  for (auto it = secondMap.cbegin(); it != secondMap.cend(); ++it)
  {
    if (resultMap.find(it->first) == resultMap.cend())
    {
      resultMap.push(it->first, it->second);
    }
  }

  addMap(args.front(), resultMap);
  result = std::string();
}

void zak::ImplementedCommands::addMap(std::string& mapName, map& toAdd)
{
  if (maps_.find(mapName) != maps_.cend())
  {
    maps_[mapName] = std::move(toAdd);
  }
  else
  {
    maps_.push(mapName, toAdd);
  }
}
