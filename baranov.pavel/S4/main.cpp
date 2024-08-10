#include <iostream>
#include <fstream>
#include "tree.hpp"
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
  if (!file.is_open())
  {
    std::cerr << "Invalid file name\n";
    return 1;
  }
  using basicTree = Tree< int, std::string >;
  using treeOfTrees = Tree< std::string, basicTree >;
  treeOfTrees trees;
  baranov::inputTrees(trees, file);
}

