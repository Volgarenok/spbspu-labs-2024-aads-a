#ifndef INPUT_DATASET
#define INPUT_DATASET
#include <istream>
#include <map>
#include <string>


namespace baranov
{
  using basicTree = std::map< int, std::string >;
  using treeOfTrees = std::map< std::string, basicTree >;
  void inputTrees(treeOfTrees & trees, std::istream & input);
}

#endif

