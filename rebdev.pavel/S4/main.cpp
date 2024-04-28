#include <iostream>

#include "myTree.hpp"

int main()
{
  rebdev::AVLTree< int, int > firstTree;
  std::cout << firstTree.size();
  std::cout << firstTree.empty();
  auto iter = firstTree.end();
  firstTree.clear();
  firstTree.clear();
  rebdev::AVLTree< int, int > secondTree;
  secondTree.swap(firstTree);
  return 0;
}
