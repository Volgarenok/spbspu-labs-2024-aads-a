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
    std::string doCommandLine(std::istream &input);

  private:
    using commandFunc = std::string (MapMaster::*)(const List<std::string> &cmdSource);

    std::map < std::string, primaryMap > &maps_;
    std::map < std::string, commandFunc > commands_;

    std::string printCmd(const List<std::string> &cmdSource);
    std::string complementCmd(const List<std::string> &cmdSource);
    std::string intersectCmd(const List<std::string> &cmdSource);
    std::string unionCmd(const List<std::string> &cmdSource);
  };
}

#endif
