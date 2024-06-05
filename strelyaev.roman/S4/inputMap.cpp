#include "inputMap.hpp"
#include <iostream>
#include <tree/binarySearchTree.hpp>

strelyaev::Tree< std::string, strelyaev::Tree< int, std::string > > strelyaev::inputMap(std::istream& in)
{
  Tree< std::string, Tree< int, std::string > > map;
  while (!in.eof())
  {
    in.clear();
    Tree< int, std::string > temp_map;
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
  return map;
}


