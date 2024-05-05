#include "binarySearchTree.hpp"
int main()
{
  strelyaev::Tree< int > tree;
  for (int i = 0; i < 10; i++)
  {
    tree.push(i);
  }
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << *it << "\n";
  }
  std::cout << "==================================\n";
  auto it2 = tree.find(9);
  std::cout << *it2;
}
