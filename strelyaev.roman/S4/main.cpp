#include "binarySearchTree.hpp"
int main()
{
  strelyaev::Tree< int > tree;
  tree.push(4);
  tree.push(5);
  tree.push(2);
  tree.push(3);
  tree.push(1);
  tree.push(0);
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << *it << "\n";
  }
  std::cout << "==================================\n";
}
