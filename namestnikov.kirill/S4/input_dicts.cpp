#include "input_dicts.hpp"

void namestnikov::inputMaps(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap)
{
  while (!in.eof())
  {
    in.clear();
    std::map< size_t, std::string > tempMap;
    std::string mapName = "";
    in >> mapName;
    size_t keyNumber = 0;
    while (in >> keyNumber)
    {
      std::string value = "";
      in >> value;
      tempMap.insert(std::make_pair(keyNumber, value));
    }
    myMap.insert(std::make_pair(mapName, tempMap));
  }
}