#include "mapMaster.hpp"

#include <iostream>

zhalilov::MapMaster::MapMaster(std::map < std::string, primaryMap > &maps):
  maps_(maps)
{
  std::pair < std::string, commandFunc > cmdPair;
  cmdPair = std::make_pair < std::string, commandFunc >("print", &MapMaster::printCmd);
  commands_.insert(cmdPair);
  cmdPair = std::make_pair < std::string, commandFunc >("complement", &MapMaster::complementCmd);
  commands_.insert(cmdPair);
  cmdPair = std::make_pair < std::string, commandFunc >("intersect", &MapMaster::intersectCmd);
  commands_.insert(cmdPair);
  cmdPair = std::make_pair < std::string, commandFunc >("union", &MapMaster::unionCmd);
  commands_.insert(cmdPair);
}

void zhalilov::MapMaster::doCommandLine(std::istream &input, std::string &result)
{
  std::ios_base::fmtflags ff(input.flags());
  input >> std::noskipws;
  List < std::string > cmdSource;
  std::string tmp;
  char delim = 0;
  while (input && delim != '\n')
  {
    input >> tmp;
    if (input)
    {
      cmdSource.push_back(tmp);
    }
    input >> delim;
  }
  input.flags(ff);

  if (cmdSource.empty())
  {
    result = std::string();
    return;
  }
  try
  {
    std::string cmdName = cmdSource.front();
    cmdSource.pop_front();
    (this->*commands_.at(cmdName))(cmdSource, result);
  }
  catch (const std::out_of_range &e)
  {
    throw std::invalid_argument("invalid command name");
  }
}

void zhalilov::MapMaster::printCmd(List < std::string > &cmdSource, std::string &result)
{
  if (cmdSource.capacity() != 1)
  {
    throw std::invalid_argument("incorrect command source");
  }

  std::string mapName = cmdSource.back();
  if (!maps_.at(mapName).empty())
  {
    auto it = maps_[mapName].cbegin();
    auto end = maps_[mapName].cend();
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
}

void zhalilov::MapMaster::complementCmd(List < std::string > &cmdSource, std::string &result)
{
  if (cmdSource.capacity() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  primaryMap &secondMap = maps_.at(cmdSource.back());
  cmdSource.pop_back();
  primaryMap &firstMap = maps_.at(cmdSource.back());
  primaryMap resultMap;

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

  addMap(cmdSource.front(), resultMap);
  result = std::string();
}

void zhalilov::MapMaster::intersectCmd(List < std::string > &cmdSource, std::string &result)
{
  if (cmdSource.capacity() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  primaryMap &secondMap = maps_.at(cmdSource.back());
  cmdSource.pop_back();
  primaryMap &firstMap = maps_.at(cmdSource.back());
  primaryMap resultMap;

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

  addMap(cmdSource.front(), resultMap);
  result = std::string();
}

void zhalilov::MapMaster::unionCmd(List < std::string > &cmdSource, std::string &result)
{
  if (cmdSource.capacity() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  primaryMap &secondMap = maps_.at(cmdSource.back());
  cmdSource.pop_back();
  primaryMap &firstMap = maps_.at(cmdSource.back());
  primaryMap resultMap;

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

  addMap(cmdSource.front(), resultMap);
  result = std::string();
}

void zhalilov::MapMaster::addMap(std::string &mapName, primaryMap &map)
{
  std::pair < std::string, primaryMap > mapsPair = std::make_pair(mapName, map);
  auto mapItAndInsertResult = maps_.insert(mapsPair);
  if (!mapItAndInsertResult.second)
  {
    (mapItAndInsertResult.first)->second = mapsPair.second;
  }
}
