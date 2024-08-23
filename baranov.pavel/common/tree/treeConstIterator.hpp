#ifndef TREE_CONST_ITERATOR_HPP
#define TREE_CONST_ITERATOR_HPP
#include <iterator>
#include <utility>
#include <cassert>
#include <tree/treeNode.hpp>

namespace baranov
{
  template< typename Key, typename T, typename Compare >
  class Tree;

  template< typename Key, typename T, typename Compare >
  class TreeConstIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    friend class Tree< Key, T, Compare >;
    using this_t = TreeConstIterator< Key, T, Compare >;

    TreeConstIterator();
    ~TreeConstIterator() = default;
    TreeConstIterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    const std::pair< Key, T > & operator*() const;
    const std::pair< Key, T > * operator->() const;

    bool operator==(const this_t &) const;
    bool operator!=(const this_t &) const;
  private:
    TreeNode< Key, T > * node_;
    explicit TreeConstIterator(TreeNode< Key, T > * node);
  };

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare >::TreeConstIterator():
    node_(nullptr)
  {}

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare >::TreeConstIterator(TreeNode< Key, T > * node):
    node_(node)
  {}

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare > & TreeConstIterator< Key, T, Compare >::operator++()
  {
    if (node_->hasRight())
    {
      node_ = node_->right_;
      while (node_->hasLeft())
      {
        node_ = node_->left_;
      }
    }
    else
    {
      while (node_->isRight())
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return * this;
  }

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare > TreeConstIterator< Key, T, Compare >::operator++(int)
  {
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare > & TreeConstIterator< Key, T, Compare >::operator--()
  {
    if (node_->hasLeft())
    {
      node_ = node_->left_;
      while (node_->hasRight())
      {
        node_ = node_->right_;
      }
    }
    else
    {
      while (node_->isLeft())
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return * this;
  }

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare > TreeConstIterator< Key, T, Compare >::operator--(int)
  {
    this_t result(*this);
    --(*this);
    return result;
  }

  template< typename Key, typename T, typename Compare >
  const std::pair< Key, T > & TreeConstIterator< Key, T, Compare >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename Key, typename T, typename Compare >
  const std::pair< Key, T > * TreeConstIterator< Key, T, Compare >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename Key, typename T, typename Compare >
  bool TreeConstIterator< Key, T, Compare >::operator==(const this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename Key, typename T, typename Compare >
  bool TreeConstIterator< Key, T, Compare >::operator!=(const this_t & rhs) const
  {
    return !(rhs == *this);
  }
}

#endif

