#include "commands.hpp"

void zhalilov::commands::printCmd(mapOfMaps &maps, List < std::string > &cmdSource, std::string &result)
{
  if (cmdSource.capacity() != 1)
  {
    throw std::invalid_argument("incorrect command source");
  }

  std::string mapName = cmdSource.back();
  if (!maps.at(mapName).empty())
  {
    auto it = maps[mapName].cbegin();
    auto end = maps[mapName].cend();
    end--;
    result = mapName + ' ';
    while (it != end)
    {
      result += std::to_string(it->first) + ' ';
      result += it->second + ' ';
      it++;
    }
    result += std::to_string(it->first) + ' ';
    result += it->second;
  }
  else
  {
    result = "<EMPTY>";
  }
}

void zhalilov::commands::complementCmd(mapOfMaps &maps, List < std::string > &cmdSource, std::string &result)
{
  if (cmdSource.capacity() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  intStringMap &secondMap = maps.at(cmdSource.back());
  cmdSource.pop_back();
  intStringMap &firstMap = maps.at(cmdSource.back());
  intStringMap resultMap;

  auto firstIt = firstMap.cbegin();
  auto firstEnd = firstMap.cend();
  while (firstIt != firstEnd)
  {
    if (secondMap.find(firstIt->first) == secondMap.end())
    {
      int currKey = firstIt->first;
      std::string currValue = firstIt->second;
      resultMap.insert(std::pair < int, std::string >(currKey, currValue));
    }
    firstIt++;
  }

  maps[cmdSource.front()] = resultMap;
  result = std::string();
}

void zhalilov::commands::intersectCmd(mapOfMaps &maps, List < std::string > &cmdSource, std::string &result)
{
  if (cmdSource.capacity() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  intStringMap &secondMap = maps.at(cmdSource.back());
  cmdSource.pop_back();
  intStringMap &firstMap = maps.at(cmdSource.back());
  intStringMap resultMap;

  auto firstIt = firstMap.cbegin();
  auto firstEnd = firstMap.cend();
  while (firstIt != firstEnd)
  {
    if (secondMap.find(firstIt->first) != secondMap.end())
    {
      int currKey = firstIt->first;
      std::string currValue = firstIt->second;
      resultMap.insert(std::pair < int, std::string >(currKey, currValue));
    }
    firstIt++;
  }

  maps[cmdSource.front()] = resultMap;
  result = std::string();
}

void zhalilov::commands::unionCmd(mapOfMaps &maps, List < std::string > &cmdSource, std::string &result)
{
  if (cmdSource.capacity() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  intStringMap &secondMap = maps.at(cmdSource.back());
  cmdSource.pop_back();
  intStringMap &firstMap = maps.at(cmdSource.back());
  intStringMap resultMap;

  auto firstIt = firstMap.cbegin();
  auto firstEnd = firstMap.cend();
  while (firstIt != firstEnd)
  {
    resultMap.insert(std::pair < int, std::string >(firstIt->first, firstIt->second));
    firstIt++;
  }

  auto secondIt = secondMap.cbegin();
  auto secondEnd = secondMap.cend();
  while (secondIt != secondEnd)
  {
    resultMap.insert(std::pair < int, std::string >(secondIt->first, secondIt->second));
    secondIt++;
  }

  maps[cmdSource.front()] = resultMap;
  result = std::string();
}
