#include "inputTree.hpp"

void baranov::inputTree(std::istream & in, Tree< int, std::string > & tree)
{
  int key = 0;
  std::string value;
  while (in >> key >> value)
  {
    tree.insert(key, value);
  }
  if (!in.eof())
  {
    throw std::logic_error("Invalid input");
  }
}

