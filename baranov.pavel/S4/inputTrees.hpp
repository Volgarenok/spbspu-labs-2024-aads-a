#ifndef INPUT_DATASET
#define INPUT_DATASET
#include <istream>
#include <string>
#include <tree/tree.hpp>

namespace baranov
{
  using basicTree = Tree< int, std::string >;
  using treeOfTrees = Tree< std::string, basicTree >;
  void inputTrees(treeOfTrees & trees, std::istream & input);
}

#endif

