#include "readingFromFile.hpp"

void belokurskaya::inputTree(std::istream& in, BinarySearchTree< int, std::string >& tree)
{
  int key = 0;
  std::string value;
  while (in >> key >> value)
  {
    tree[key] = value;
  }
}
