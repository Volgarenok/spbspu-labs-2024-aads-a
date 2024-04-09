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

std::string zhalilov::MapMaster::doCommandLine(std::istream &input)
{
  std::string commandName;
  std::string commandSource;
  input >> commandName;
  std::getline(input, commandSource);
  commandFunc function = commands_[commandName];
  return (this->*function)(commandSource);
}

std::string zhalilov::MapMaster::printCmd(const std::string &cmdLine)
{

}

std::string zhalilov::MapMaster::complementCmd(const std::string &cmdLine)
{}

std::string zhalilov::MapMaster::intersectCmd(const std::string &cmdLine)
{}

std::string zhalilov::MapMaster::unionCmd(const std::string &cmdLine)
{}
