#include "inputTrees.hpp"

void baranov::inputTrees(treeOfTrees & trees, std::istream & input)
{
  std::string dictName;
  int key;
  std::string value;
  while (input)
  {
    input >> dictName;
    basicTree tree;
    while (input)
    {
      input >> key >> value;
      tree.insert(std::pair< int, std::string >(key, value));
    }
    if (!input.eof())
    {
      input.clear();
    }
    trees.insert(std::pair< std::string, basicTree >(dictName, tree));
  }
}

