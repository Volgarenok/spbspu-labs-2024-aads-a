#include "inputMaps.hpp"
#include <istream>

void zakozhurnikova::inputMaps(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< int, std::string > >& maps)
{
  ScopeGuard guard(in);
  int key = 0;
  std::string value;
  std::string nameTree;
  while (in)
  {
    BinarySearchTree< int, std::string > tree;
    in >> nameTree;
    while (in >> key >> value)
    {
      tree.push(key, value);
    }
    if (!in.eof())
    {
      in.clear();
    }
    maps.push(nameTree, tree);
  }
}
