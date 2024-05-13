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
    using intStringMap = TwoThree < int, std::string >;
    using mapOfMaps = TwoThree < std::string, intStringMap >;
    using commandFunc = void (*)(mapOfMaps &, List < std::string > &, std::string &);

    explicit MapMaster(TwoThree < std::string, intStringMap > &maps);
    void doCommandLine(std::istream &input, std::string &result);
    void addCommand(std::string name, commandFunc func);

  private:
    mapOfMaps &maps_;
    TwoThree < std::string, commandFunc > commands_;
  };
}

#endif
