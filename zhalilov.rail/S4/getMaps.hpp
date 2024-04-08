#ifndef GETMAPS_HPP
#define GETMAPS_HPP

#include <map>
#include <iosfwd>

namespace zhalilov
{
  using primaryMap = std::map < int, std::string >;
  void getMaps(std::map < std::string, primaryMap > &maps, std::istream &input);
}

#endif
