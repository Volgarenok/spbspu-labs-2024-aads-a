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
    while (input && input.peek() != '\n')
    {
      input >> key >> value;
      tree.insert(key, value);
    }
    trees.insert(dictName, tree);
  }
}

