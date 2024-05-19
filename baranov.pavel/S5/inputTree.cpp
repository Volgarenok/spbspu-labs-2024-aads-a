#include "inputTree.hpp"

void baranov::inputTree(std::istream & in, std::map< int, std::string > & tree)
{
  int key = 0;
  std::string value;
  while (in >> key >> value)
  {
    tree[key] = value;
  }
}

