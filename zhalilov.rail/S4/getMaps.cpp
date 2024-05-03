#include "getMaps.hpp"

#include <istream>

#include "twoThreeTree.hpp"

void zhalilov::getMaps(TwoThree < std::string, primaryMap > &maps, std::istream &input)
{
  int key = 0;
  std::string value;
  std::string name;
  using primaryMapPair = std::pair < int, std::string >;
  using mapOfMapsPair = std::pair < std::string, primaryMap >;
  while (input)
  {
    primaryMap basicMap;
    input >> name;
    while (input >> key >> value)
    {
      basicMap.insert(primaryMapPair(key, value));
    }
    if (!input.eof())
    {
      input.clear();
    }
    maps.insert(mapOfMapsPair(name, basicMap));
  }
}
