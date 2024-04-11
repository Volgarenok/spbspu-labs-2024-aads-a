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
    return;
  }
  std::string cmdName = cmdSource.front();
  cmdSource.pop_front();
  (this->*commands_[cmdName])(cmdSource, result);
}

void zhalilov::MapMaster::printCmd(const List < std::string > &cmdSource, std::string &result)
{
  if (cmdSource.capacity() != 1)
  {
    throw std::invalid_argument("incorrect command");
  }
  auto it = maps_.at(cmdSource.front()).begin();
  auto end = maps_.at(cmdSource.front()).end();
  result = cmdSource.front();
  while (it != end)
  {
    result += std::to_string(it->first);
    result += it->second;
  }
}

void zhalilov::MapMaster::complementCmd(const List < std::string > &cmdSource, std::string &result)
{}

void zhalilov::MapMaster::intersectCmd(const List < std::string > &cmdSource, std::string &result)
{}

void zhalilov::MapMaster::unionCmd(const List < std::string > &cmdSource, std::string &result)
{}
