#include "inputMaps.hpp"

void marishin::inputMaps(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap)
{
  while (!in.eof())
  {
    in.clear();
    Tree< size_t, std::string > tempMap;
    std::string mapName = "";
    in >> mapName;
    size_t keyNumber = 0;
    while (in >> keyNumber)
    {
      std::string value = "";
      in >> value;
      tempMap.insert(keyNumber, value);
    }
    myMap.insert(mapName, tempMap);
  }
}
