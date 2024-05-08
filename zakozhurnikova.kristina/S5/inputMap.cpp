#include "inputMap.hpp"
#include <istream>

void zakozhurnikova::inputMap(std::istream& in, BinarySearchTree< long long, std::string >& map)
{
  ScopeGuard guard(in);
  int key = 0;
  std::string value;
  while (in)
  {
    BinarySearchTree< long long, std::string > tree;
    while (in >> key >> value)
    {
      tree.push(key, value);
    }
    if (!in.eof())
    {
      in.clear();
    }
    map = tree;
  }
}
