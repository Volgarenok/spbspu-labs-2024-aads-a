#include <iostream>
#include "AVLTree.hpp"
int main()
{
  AVLTree< int > tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);

  std::cout << tree.search(1);

  tree.print();
}
