#include "binarySearchTree.hpp"
int main()
{
  strelyaev::Tree< int > tree;
  int a = 5;
  tree.push(a);
  tree.push(4);
  tree.push(3);
  tree.push(6);
  std::cout << tree.root->right_->value_;
}
