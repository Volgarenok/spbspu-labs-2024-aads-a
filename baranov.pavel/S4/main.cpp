#include <iostream>
#include <fstream>
#include <map>
#include "inputTrees.hpp"

int main(int argc, char ** argv)
{
  using namespace baranov;
  if (argc != 2)
  {
    std::cerr << "Invalid CLA\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  using basicTree = std::map< int, std::string >;
  using treeOfTrees = std::map< std::string, basicTree >;
  treeOfTrees trees;
  baranov::inputTrees(trees, file);
}
