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
    using commandFunc = void (MapMaster::*)(const List < std::string > &, std::string &);

    std::map < std::string, primaryMap > &maps_;
    std::map < std::string, commandFunc > commands_;

    void printCmd(const List < std::string > &cmdSource, std::string &result);
    void complementCmd(const List < std::string > &cmdSource, std::string &result);
    void intersectCmd(const List < std::string > &cmdSource, std::string &result);
    void unionCmd(const List < std::string > &cmdSource, std::string &result);
  };
}

#endif
