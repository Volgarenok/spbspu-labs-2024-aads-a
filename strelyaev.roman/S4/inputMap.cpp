#include "inputMap.hpp"
#include <iostream>

void strelyaev::inputMap(std::istream& in, std::map< std::string, std::map< int, std::string > >& map)
{
  while (!in.eof())
  {
    in.clear();
    std::map< int, std::string > temp_map;
    std::string map_name = "";
    in >> map_name;
    int key_number = 0;
    while (in >> key_number)
    {
      std::string key_name = "";
      in >> key_name;
      temp_map.insert(std::make_pair(key_number, key_name));
    }
    map.insert(std::make_pair(map_name, temp_map));
  }
}