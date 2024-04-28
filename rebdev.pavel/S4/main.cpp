#include <iostream>

#include "myTree.hpp"

int main()
{
  rebdev::AVLTree< int, int > firstTree;
  std::cout << firstTree.size();
  std::cout << firstTree.empty();
  auto iter = firstTree.end();
  return 0;
}
