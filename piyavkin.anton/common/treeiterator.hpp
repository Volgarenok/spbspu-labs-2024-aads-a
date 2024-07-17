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
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
  public:
    using reference = std::pair< Key, T >&;
    using pointer = std::pair< Key, T >*;
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
        while (node_->left_)
        {
          node_ = node_->left_;
        }
        return *this;
      }
      while (node_->parent_ && node_->parent_->right_ == node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
      return *this;
    }
    TreeIterator< Key, T, Compare >& operator--()
    {
      if (node_->left_)
      {
        node_ = node_->left_;
        while (node_->right_)
        {
          node_ = node_->right_;
        }
        return *this;
      }
      while (node_->parent_ && node_->parent_->left_ == node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
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
      return !(node_ == rhs.node_);
    }
    pointer operator->()
    {
      return std::addressof(node_->val_type);
    }
    reference operator*()
    {
      return node_->val_type;
    }
    const val_type* operator->() const
    {
      return std::addressof(node_->val_type);
    }
    const val_type& operator*() const
    {
      return node_->val_type;
    }
  private:
    detail::TreeNode< Key, T >* node_;
    explicit TreeIterator(detail::TreeNode< Key, T >* node):
      node_(node)
    {}
  };
  template< class Key, class T, class Compare >
  class ConstLnrIterator;
  template< class Key, class T, class Compare >
  class ConstBreadthIterator;
  template< class Key, class T, class Compare >
  class ConstRnlIterator;
  template< class Key, class T, class Compare = std::less< Key > >
  class ConstTreeIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
  public:
    using reference = const std::pair< Key, T >&;
    using pointer = const std::pair< Key, T >*;
    ConstTreeIterator():
      node_(nullptr)
    {}
    ConstTreeIterator(const ConstLnrIterator< Key, T, Compare >& it):
      ConstTreeIterator(it.stack.top())
    {}
    ConstTreeIterator(const ConstRnlIterator< Key, T, Compare >& it):
      ConstTreeIterator(it.stack.top())
    {}
    ConstTreeIterator(const ConstBreadthIterator< Key, T, Compare >& it):
      ConstTreeIterator(it.stack.top())
    {}
    ConstTreeIterator(const ConstTreeIterator< Key, T, Compare >&) = default;
    ConstTreeIterator< Key, T, Compare >& operator=(const ConstTreeIterator< Key, T, Compare >&) = default;
    ConstTreeIterator< Key, T, Compare >& operator=(const ConstLnrIterator< Key, T, Compare >& it)
    {
      node_ = it.stack.top();
    }
    ConstTreeIterator< Key, T, Compare >& operator=(const ConstRnlIterator< Key, T, Compare >& it)
    {
      node_ = it.stack.top();
    }
    ConstTreeIterator< Key, T, Compare >& operator=(const ConstBreadthIterator< Key, T, Compare >& it)
    {
      node_ = it.stack.top();
    }
    ~ConstTreeIterator() = default;
    ConstTreeIterator< Key, T, Compare >& operator++()
    {
      if (node_->right_)
      {
        node_ = node_->right_;
        while (node_->left_)
        {
          node_ = node_->left_;
        }
        return *this;
      }
      while (node_->parent_ && node_->parent_->right_ == node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
      return *this;
    }
    ConstTreeIterator< Key, T, Compare >& operator--()
    {
      if (node_->left_)
      {
        node_ = node_->left_;
        while (node_->right_)
        {
          node_ = node_->right_;
        }
        return *this;
      }
      while (node_->parent_ && node_->parent_->left_ == node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
      return *this;
    }
    ConstTreeIterator< Key, T, Compare > operator++(int)
    {
      ConstTreeIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    ConstTreeIterator< Key, T, Compare > operator--(int)
    {
      ConstTreeIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const ConstTreeIterator< Key, T, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const ConstTreeIterator< Key, T, Compare >& rhs) const
    {
      return !(node_ == rhs.node_);
    }
    pointer operator->() const
    {
      return std::addressof(node_->val_type);
    }
    reference operator*() const
    {
      return node_->val_type;
    }
  private:
    detail::TreeNode< Key, T >* node_;
    explicit ConstTreeIterator(detail::TreeNode< Key, T >* node):
      node_(node)
    {}
  };
}
#endif
