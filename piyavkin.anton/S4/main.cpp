#include <iostream>
#include "tree.hpp"

int main()
{
  piyavkin::Tree< int, int > tree;
  std::cout << tree.size() << ' ' << tree.empty();
  tree.insert(std::make_pair< int, int >(5, 5));
  std::cout << tree.size() << ' ' << tree.empty();
  std::cout << tree.root_->data_;
  tree.insert(std::make_pair< int, int >(6, 6));
  tree.insert(std::make_pair< int, int >(4, 4));
  std::cout << tree.root_->left_->data_;
  std::cout << ' ' << tree.root_->right_->data_;
}