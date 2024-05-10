#include "commands.hpp"
#include "implementedCommands.hpp"

namespace zak = zakozhurnikova;

void addMap(std::string& mapName, zak::map& toAdd, zak::tree& maps_)
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

void zak::print(List< std::string >& args, std::string& result, tree& maps_)
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

void zak::complement(List< std::string >& args, std::string& result, tree& maps_)
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

  addMap(args.front(), resultMap, maps_);
  result = std::string();
}

void zak::intersect(List< std::string >& args, std::string& result, tree& maps_)
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

  addMap(args.front(), resultMap, maps_);
  result = std::string();
}

void zak::doUnion(List< std::string >& args, std::string& result, tree& maps_)
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

  addMap(args.front(), resultMap, maps_);
  result = std::string();
}
