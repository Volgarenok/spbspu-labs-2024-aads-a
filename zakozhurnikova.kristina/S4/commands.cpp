#include "commands.hpp"
#include <stdexcept>
#include "implementedCommands.hpp"

namespace zak = zakozhurnikova;

void addMap(std::string& mapName, zak::map& toAdd, zak::tree& maps)
{
  if (maps.find(mapName) != maps.cend())
  {
    maps[mapName] = std::move(toAdd);
  }
  else
  {
    maps.push(mapName, toAdd);
  }
}

void zak::print(const List< std::string >& args, std::string& result, const tree& maps)
{
  if (args.size() != 1)
  {
    throw std::invalid_argument("incorrect command source");
  }

  std::string mapName = args.back();
  if (!maps.at(mapName).empty())
  {
    result = mapName + ' ';
    for (auto it = maps[mapName].cbegin(); it != maps[mapName].cend(); ++it)
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

void zak::complement(List< std::string >& args, std::string& result, tree& maps)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  map& secondMap = maps.at(args.back());
  args.pop_back();
  map& firstMap = maps.at(args.back());
  map resultMap;

  for (auto it = firstMap.cbegin(); it != firstMap.cend(); ++it)
  {
    if (secondMap.find(it->first) == secondMap.cend())
    {
      resultMap.push(it->first, it->second);
    }
  }

  addMap(args.front(), resultMap, maps);
  result = std::string();
}

void zak::intersect(List< std::string >& args, std::string& result, tree& maps)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  map& secondMap = maps.at(args.back());
  args.pop_back();
  map& firstMap = maps.at(args.back());
  map resultMap;

  for (auto it = firstMap.cbegin(); it != firstMap.cend(); ++it)
  {
    if (secondMap.find(it->first) != secondMap.cend())
    {
      resultMap.push(it->first, it->second);
    }
  }

  addMap(args.front(), resultMap, maps);
  result = std::string();
}

void zak::doUnion(List< std::string >& args, std::string& result, tree& maps)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  map& secondMap = maps.at(args.back());
  args.pop_back();
  map& firstMap = maps.at(args.back());
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

  addMap(args.front(), resultMap, maps);
  result = std::string();
}
