#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>
#include <functional>

namespace nikitov
{
  template< class Key, class T, class Compare = std::less< Key > >
  struct TreeNode
  {
    TreeNode();
    TreeNode(const Key& key, const T& value);
    ~TreeNode() = default;

    void add(const Key& key, const T& value);
    void clear();

    std::pair< Key, T > firstValue_;
    std::pair< Key, T > secondValue_;
    Tree< Key, T, Compare >* left_;
    Tree< Key, T, Compare >* middle_;
    Tree< Key, T, Compare >* right_;
    Tree< Key, T, Compare >* parent_;
    size_t size_;
    Compare cmp_;
  };

  template< class Key, class T, class Compare >
  TreeNode< Key, T, Compare >::TreeNode():
    Tree(Key(), T())
  {}

  template< class Key, class T, class Compare >
  TreeNode< Key, T, Compare >::TreeNode(const Key& key, const T& value):
    firstValue_({ key, value }),
    secondValue_({ Key(), T() }),
    left_(nullptr),
    middle_(nullptr),
    right_(nullptr),
    parent_(nullptr),
    size_(1),
    cmp_(Compare())
  {}

  template< class Key, class T, class Compare >
  void TreeNode< Key, T, Compare >::add(const Key& key, const T& value)
  {
    secondValue_ = { key, value };
    if (!cmp_(firstValue_.first, secondValue_.first))
    {
      std::swap(firstValue_, secondValue_);
    }
    ++size_;
  }

  template< class Key, class T, class Compare >
  void TreeNode< Key, T, Compare >::clear()
  {
    if (left_)
    {
      left_->clear();
      delete left_;
    }
    if (middle_)
    {
      middle_->clear();
      delete middle_;
    }
    if (right_)
    {
      right_->clear();
      delete right_;
    }
  }
}
#endif
