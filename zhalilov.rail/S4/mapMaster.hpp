#ifndef MAPMASTER_HPP
#define MAPMASTER_HPP

#include <map>
#include <string>
#include <iosfwd>

#include <list/list.hpp>

namespace zhalilov
{
  class MapMaster
  {
  public:
    using primaryMap = std::map < int, std::string >;

    explicit MapMaster(std::map < std::string, primaryMap > &maps);
    void doCommandLine(std::istream &input, std::string &result);

  private:
    using commandFunc = void (MapMaster::*)(List < std::string > &, std::string &);

    std::map < std::string, primaryMap > &maps_;
    std::map < std::string, commandFunc > commands_;

    void printCmd(List < std::string > &cmdSource, std::string &result);
    void complementCmd(List < std::string > &cmdSource, std::string &result);
    void intersectCmd(List < std::string > &cmdSource, std::string &result);
    void unionCmd(List < std::string > &cmdSource, std::string &result);

    void addMap(std::string &mapName, primaryMap &map);
  };
}

#endif
