#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP
#include <iterator>
#include "treenode.hpp"

namespace piyavkin
{
  template< class Key, class T, class Compare >
  class Tree;
  template< class Key, class T, class Compare = std::less< Key > >
  class TreeIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
  public:
    TreeIterator():
      node_(nullptr)
    {}
    TreeIterator(const TreeIterator< Key, T, Compare >&) = default;
    TreeIterator< Key, T, Compare >& operator=(const TreeIterator< Key, T, Compare >&) = default;
    ~TreeIterator() = default;
    TreeIterator< Key, T, Compare >& operator++()
    {
      if (node_->right_)
      {
        node_ = node_->right_;
        return *this;
      }
      while (!node_->right_ && node_->parent_->right_ == node_)
      {
        node_ = node_->parent_;
      }
      return *this;
    }
    TreeIterator< Key, T, Compare >& operator--()
    {
      if (node_->left_)
      {
        node_ = node_->left_;
        return *this;
      }
      while (!node_->left_ && node_->parent_->left_ == node_)
      {
        node_ = node_->parent_;
      }
      return *this;
    }
    TreeIterator< Key, T, Compare > operator++(int)
    {
      TreeIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    TreeIterator< Key, T, Compare > operator--(int)
    {
      TreeIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const TreeIterator< Key, T, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const TreeIterator< Key, T, Compare >& rhs) const
    {
      return !(*this == rhs);
    }
    T* operator->()
    {
      return std::addressof(node_->data_);
    }
    T& operator*()
    {
      return node_->data_;
    }
    const T* operator->() const
    {
      return std::addressof(node_->data_);
    }
    const T& operator*() const
    {
      return node_->data_;
    }
  private:
    detail::Node< Key, T >* node_;
    explicit TreeIterator(detail::Node< Key, T >* node):
      node_(node)
    {}
  };
}
#endif