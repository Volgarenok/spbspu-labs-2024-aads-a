#ifndef MAPMASTER_HPP
#define MAPMASTER_HPP

#include <string>
#include <iosfwd>

#include <list/list.hpp>

#include "twoThreeTree.hpp"

namespace zhalilov
{
  class MapMaster
  {
  public:
    using primaryMap = TwoThree < int, std::string >;

    explicit MapMaster(TwoThree < std::string, primaryMap > &maps);
    void doCommandLine(std::istream &input, std::string &result);

  private:
    using commandFunc = void (MapMaster::*)(List < std::string > &, std::string &);

    TwoThree < std::string, primaryMap > &maps_;
    TwoThree < std::string, commandFunc > commands_;

    void printCmd(List < std::string > &cmdSource, std::string &result);
    void complementCmd(List < std::string > &cmdSource, std::string &result);
    void intersectCmd(List < std::string > &cmdSource, std::string &result);
    void unionCmd(List < std::string > &cmdSource, std::string &result);

    void addMap(std::string &mapName, primaryMap &map);
  };
}

#endif
