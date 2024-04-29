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
    void clear();
    size_t size() const;
    bool empty() const;

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

  template< class Key, class T, class Compare >
  size_t BinarySearchTree< Key, T, Compare >::size() const
  {
    return size_;
  }

  template< class Key, class T, class Compare >
  bool BinarySearchTree< Key, T, Compare >::empty() const
  {
    return !size_;
  }
}
#endif
