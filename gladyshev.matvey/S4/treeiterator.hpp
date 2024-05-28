#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP

#include <memory>
#include <iterator>
#include <functional>

#include "treenode.hpp"

namespace gladyshev
{
  template < class Key, class Value, class Compare >
  struct Tree;
  template < class Key, class Value, class Compare = std::less < Key > >
  struct TIterator: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
  public:
    using tnode = detail::TNode< Key, Value >;
    TIterator():
      node_(nullptr)
    {}
    TIterator(const TIterator< Key, Value, Compare >& rhs) = default;
    ~TIterator() = default;
    TIterator< Key, Value, Compare >& operator=(const TIterator< Key, Value, Compare >& rhs) = default;
    TIterator< Key, Value, Compare >& operator++()
    {
      if (node_->right)
      {
        node_ = node_->right;
        while (node_->left)
        {
          node_ = node_->left;
        }
        return *this;
      }
      while (node_->parent && node_->parent->right == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
      return *this;
    }
    TIterator< Key, Value, Compare >& operator--()
    {
      if (node_->left)
      {
        node_ = node_->left;
        while (node_->right)
        {
          node_ = node_->right;
        }
        return *this;
      }
      while (node_->parent && node_->parent->left == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
      return *this;
    }
    TIterator< Key, Value, Compare > operator++(int)
    {
      TIterator< Key, Value > result(*this);
      ++(*this);
      return result;
    }
    TIterator< Key, Value, Compare > operator--(int)
    {
      TIterator< Key, Value, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator!=(const TIterator< Key, Value, Compare >& rhs) const
    {
      return !(*this == rhs);
    }
    bool operator==(const TIterator< Key, Value, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }
    const std::pair< Key, Value >* operator->() const
    {
      return std::addressof(node_->data);
    }
    const std::pair< Key, Value >& operator*() const
    {
      return node_->data;
    }
    std::pair< Key, Value >* operator->()
    {
      return std::addressof(node_->data);
    }
    std::pair< Key, Value >& operator*()
    {
      return node_->data;
    }
  private:
    friend Tree< Key, Value, Compare >;
    explicit TIterator(tnode* node):
      node_(node)
    {}
    tnode* node_;
  };
  template < class Key, class Value, class Compare >
  struct Tree;
  template < class Key, class Value, class Compare = std::less < Key > >
  struct CTIterator: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
  public:
    using tnode = detail::TNode< Key, Value >;
    CTIterator():
      node_(nullptr)
    {}
    CTIterator(const CTIterator< Key, Value, Compare >& rhs) = default;
    ~CTIterator() = default;
    CTIterator< Key, Value, Compare >& operator=(const CTIterator< Key, Value, Compare >& rhs) = default;
    CTIterator< Key, Value, Compare >& operator++()
    {
      if (node_->right)
      {
        node_ = node_->right;
        while (node_->left)
        {
          node_ = node_->left;
        }
        return *this;
      }
      while (node_->parent && node_->parent->right == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
      return *this;
    }
    CTIterator< Key, Value, Compare >& operator--()
    {
      if (node_->left)
      {
        node_ = node_->left;
        while (node_->right)
        {
          node_ = node_->right;
        }
        return *this;
      }
      while (node_->parent && node_->parent->left == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
      return *this;
    }
    CTIterator< Key, Value, Compare > operator++(int)
    {
      CTIterator< Key, Value > result(*this);
      ++(*this);
      return result;
    }
    CTIterator< Key, Value, Compare > operator--(int)
    {
      CTIterator< Key, Value, Compare > result(*this);
      --(*this);
      return result;
    }
    const std::pair< Key, Value >* operator->() const
    {
      return std::addressof(node_->data);
    }
    const std::pair< Key, Value >& operator*() const
    {
      return node_->data;
    }
    bool operator!=(const CTIterator< Key, Value, Compare >& rhs) const
    {
      return !(*this == rhs);
    }
    bool operator==(const CTIterator< Key, Value, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }
  private:
    friend Tree< Key, Value, Compare >;
    explicit CTIterator(tnode* node):
      node_(node)
    {}
    tnode* node_;
  };
}

#endif
