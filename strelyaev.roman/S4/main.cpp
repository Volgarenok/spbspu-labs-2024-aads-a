#include "binarySearchTree.hpp"
int main()
{
  strelyaev::Tree< int > tree;
  int a = 5;
  tree.push(5);
  tree.push(4);
  tree.push(3);
  tree.push(6);
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << *it << "\n";
  }
}
