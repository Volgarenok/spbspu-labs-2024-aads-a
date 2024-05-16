#ifndef GETMAPS_HPP
#define GETMAPS_HPP

#include <iosfwd>

#include "twoThreeTree.hpp"

namespace zhalilov
{
  using primaryMap = TwoThree < int, std::string >;
  void getMaps(TwoThree < std::string, primaryMap > &maps, std::istream &input);
}

#endif
