#include "inputMaps.hpp"
#include <istream>

void marishin::inputMaps(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< int, std::string > >& maps)
{
  int key = 0;
  std::string value;
  std::string nameTree;
  while (in && in.eof())
  {
    BinarySearchTree< int, std::string > tree;
    in >> nameTree;
    while (in >> key >> value)
    {
      tree.push(key, value);
    }
    maps.push(nameTree, tree);
  }
}
