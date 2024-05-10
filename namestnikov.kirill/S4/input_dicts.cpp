#include "input_dicts.hpp"

void namestnikov::inputMaps(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap)
{
  std::cout << "hello";
  while (!in.eof())
  {
    in.clear();
    std::cout << "hello";
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