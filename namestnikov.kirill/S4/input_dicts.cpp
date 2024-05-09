#include "input_dicts.hpp"

void namestnikov::inputMaps(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap)
{
  std::cout << "hello";
  /*while (!in.eof())
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
      tempMap.insert(std::make_pair(keyNumber, value));
    }
    myMap.insert(std::make_pair(mapName, tempMap));
  }*/
  size_t key = 0;
  std::string value;
  std::string nameTree;
  while (in)
  {
    Tree< size_t, std::string > tree;
    in >> nameTree;
    while (in >> key >> value)
    {
      tree.insert(key, value);
    }
    if (!in.eof())
    {
      in.clear();
    }
    myMap.insert(nameTree, tree);
  }
}