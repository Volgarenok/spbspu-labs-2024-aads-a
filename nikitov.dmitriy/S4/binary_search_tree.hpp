#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "tree.hpp"

namespace nikitov
{
  template< class Key, class T, class Compare >
  class BinarySearchTree
  {
  public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(Key& key, T& value);

  private:
    Tree< Key, T, Compare >* root_;
    size_t size_;
    Compare cmp_;
  };

  template< class Key, class T, class Compare >
  BinarySearchTree< Key, T, Compare >::BinarySearchTree():
    root_(Tree()),
    size_(0),
    cmp_(Compare())
  {}
}
#endif
