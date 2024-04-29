#ifndef TREE_HPP
#define TREE_HPP

#include "tree_node.hpp"
#include <functional>

namespace nikitov
{
  template< class Key, class T, class Compare = std::less< Key > >
  class Tree
  {
  public:
    Tree();
    ~Tree();

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
  Tree< Key, T, Compare >::Tree():
    root_(new Tree< Key, T, Compare >()),
    size_(0),
    cmp_(Compare())
  {}

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::~Tree()
  {
    clear();
    delete root_;
  }

  template< class Key, class T, class Compare >
  void Tree< Key, T, Compare >::clear()
  {
    if (!empty())
    {
      root_->clear();
      root_ = root_->parent_;
      delete root_->middle_;
      size_ = 0;
    }
  }

  template< class Key, class T, class Compare >
  size_t Tree< Key, T, Compare >::size() const
  {
    return size_;
  }

  template< class Key, class T, class Compare >
  bool Tree< Key, T, Compare >::empty() const
  {
    return !size_;
  }
}
#endif
