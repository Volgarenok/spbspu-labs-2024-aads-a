#include "mapMaster.hpp"

#include <iostream>

zhalilov::MapMaster::MapMaster(TwoThree < std::string, intStringMap > &maps):
  maps_(maps)
{}

void zhalilov::MapMaster::doCommandLine(std::istream &input, std::string &result)
{
  std::ios_base::fmtflags ff(input.flags());
  input >> std::noskipws;
  List < std::string > cmdSource;
  std::string tmp;
  char delim = 0;
  try
  {
    while (input && delim != '\n')
    {
      input >> tmp;
      if (input)
      {
        cmdSource.push_back(tmp);
      }
      input >> delim;
    }
  }
  catch (...)
  {
    input.flags(ff);
    throw;
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
    commands_.at(cmdName)(maps_, cmdSource, result);
  }
  catch (const std::out_of_range &e)
  {
    throw std::invalid_argument("invalid command name");
  }
}

void zhalilov::MapMaster::addCommand(std::string name, commandFunc func)
{
  commands_[name] = func;
}
