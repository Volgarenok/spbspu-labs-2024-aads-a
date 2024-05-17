#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <iosfwd>

#include <list/list.hpp>

#include "twoThreeTree.hpp"

namespace zhalilov
{
  using intStringMap = TwoThree < int, std::string >;
  using mapOfMaps = TwoThree < std::string, intStringMap >;

  namespace commands
  {
    void printCmd(mapOfMaps &, List < std::string > &cmdSource, std::string &result);
    void complementCmd(mapOfMaps &, List < std::string > &cmdSource, std::string &result);
    void intersectCmd(mapOfMaps &, List < std::string > &cmdSource, std::string &result);
    void unionCmd(mapOfMaps &, List < std::string > &cmdSource, std::string &result);
  }
}

#endif
