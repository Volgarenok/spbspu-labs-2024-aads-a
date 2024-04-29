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
    val_type* operator->()
    {
      return std::addressof(node_->val_type);
    }
    val_type& operator*()
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
  template< class Key, class T, class Compare = std::less< Key > >
  class ConstTreeIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
  public:
    ConstTreeIterator():
      node_(nullptr)
    {}
    ConstTreeIterator(const ConstTreeIterator< Key, T, Compare >&) = default;
    ConstTreeIterator< Key, T, Compare >& operator=(const ConstTreeIterator< Key, T, Compare >&) = default;
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
    const val_type* operator->() const
    {
      return std::addressof(node_->val_type);
    }
    const val_type& operator*() const
    {
      return node_->val_type;
    }
  private:
    const detail::TreeNode< Key, T >* node_;
    explicit ConstTreeIterator(const detail::TreeNode< Key, T >* node):
      node_(node)
    {}
  };
  template< class Key, class T, class Compare = std::less< Key > >
  class TreeReverseIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
  public:
    TreeReverseIterator():
      node_(nullptr)
    {}
    TreeReverseIterator(const TreeReverseIterator< Key, T, Compare >&) = default;
    TreeReverseIterator< Key, T, Compare >& operator=(const TreeReverseIterator< Key, T, Compare >&) = default;
    ~TreeReverseIterator() = default;
    TreeReverseIterator< Key, T, Compare >& operator--()
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
    TreeReverseIterator< Key, T, Compare >& operator++()
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
    TreeReverseIterator< Key, T, Compare > operator++(int)
    {
      TreeReverseIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    TreeReverseIterator< Key, T, Compare > operator--(int)
    {
      TreeReverseIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const TreeReverseIterator< Key, T, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const TreeReverseIterator< Key, T, Compare >& rhs) const
    {
      return !(node_ == rhs.node_);
    }
    val_type* operator->()
    {
      return std::addressof(node_->val_type);
    }
    val_type& operator*()
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
    explicit TreeReverseIterator(detail::TreeNode< Key, T >* node):
      node_(node)
    {}
  };
  template< class Key, class T, class Compare = std::less< Key > >
  class ConstTreeReverseIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
  public:
    ConstTreeReverseIterator():
      node_(nullptr)
    {}
    ConstTreeReverseIterator(const ConstTreeReverseIterator< Key, T, Compare >&) = default;
    ConstTreeReverseIterator< Key, T, Compare >& operator=(const ConstTreeReverseIterator< Key, T, Compare >&) = default;
    ~ConstTreeReverseIterator() = default;
    ConstTreeReverseIterator< Key, T, Compare >& operator--()
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
    ConstTreeReverseIterator< Key, T, Compare >& operator++()
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
    ConstTreeReverseIterator< Key, T, Compare > operator++(int)
    {
      ConstTreeReverseIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    ConstTreeReverseIterator< Key, T, Compare > operator--(int)
    {
      ConstTreeReverseIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const ConstTreeReverseIterator< Key, T, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const ConstTreeReverseIterator< Key, T, Compare >& rhs) const
    {
      return !(node_ == rhs.node_);
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
    const detail::TreeNode< Key, T >* node_;
    explicit ConstTreeReverseIterator(const detail::TreeNode< Key, T >* node):
      node_(node)
    {}
  };
}
#endif