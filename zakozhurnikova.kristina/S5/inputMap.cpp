#include "inputMap.hpp"
#include <istream>
#include <stdexcept>

void zakozhurnikova::inputMap(std::istream& in, BinarySearchTree< int, std::string >& map)
{
  ScopeGuard guard(in);
  int key = 0;
  std::string value;
  while (in)
  {
    BinarySearchTree< int, std::string > tree;
    while (in >> key >> value)
    {
      tree.push(key, value);
    }
    if (!in.eof())
    {
      throw std::logic_error("Incorrect input");
    }
    map = tree;
  }
}
