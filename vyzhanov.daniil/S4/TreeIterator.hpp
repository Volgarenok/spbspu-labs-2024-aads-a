#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP

#include "TreeNode.hpp"
#include <functional>
#include <iterator>
#include <utility>

namespace vyzhanov
{

  template < class Key, class Value, class Comparator >
  class AVLTree;

  template < class Key, class Value, class Comparator = std::less< Key > >
  struct TreeIterator: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
    friend class AVLTree< Key, Value, Comparator >;
    using iterator = TreeIterator< Key, Value, Comparator >;
    using TreeNode = detail::TreeNode< Key, Value >;
    using pair = std::pair< Key, Value >;

    TreeIterator();
    TreeIterator(const iterator&) = default;
    ~TreeIterator() = default;
    iterator& operator=(const iterator&) = default;
    iterator& operator=(iterator&&) = default;
    iterator& operator++();
    iterator& operator++(int);
    iterator& operator--();
    iterator& operator--(int);
    bool operator==(const TreeIterator< Key, Value, Comparator >&) const;
    bool operator!=(const TreeIterator< Key, Value, Comparator >&) const;
    const pair& operator*() const;
    const pair* operator->() const;
    pair& operator*();
    pair* operator->();

  private:
    TreeNode* node_;
    TreeIterator(TreeNode* node);
  };

  template < class Key, class Value, class Comparator >
  TreeIterator< Key, Value, Comparator >::TreeIterator():
    node_(nullptr)
  {}

  template < class Key, class Value, class Comparator >
  TreeIterator< Key, Value, Comparator >::TreeIterator(TreeNode* node) :
    node_(node)
  {}

  template < class Key, class Value, class Comparator >
  TreeIterator< Key, Value, Comparator >& TreeIterator< Key,
    Value, Comparator >::operator++()
  {
    if (node_ == nullptr)
    {
      return *this;
    }
    if (node_->right != nullptr)
    {
      node_ = node_->right;
      while (node_->left)
      {
        node_ = node_->left;
      }
      return *this;
    }
    else
    {
      auto parent = node_->parent;
      while (parent != nullptr && node_ == parent->right)
      {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }

  template < class Key, class Value, class Comparator >
  TreeIterator< Key, Value, Comparator >& TreeIterator< Key,
    Value, Comparator >::operator++(int)
  {
    iter< Key, Value, Comparator > result = *this;
    ++(*this);
    return result;
  }

  template < class Key, class Value, class Comparator >
  TreeIterator< Key, Value, Comparator >& TreeIterator< Key,
    Value, Comparator >::operator--()
  {
    if (node_ == nullptr)
    {
      return *this;
    }
    if (node_->left != nullptr)
    {
      node_ = node_->left;
      while (node_->left)
      {
        node_ = node_->left;
      }
      return *this;
    }
    else
    {
      auto parent = node_->parent;
      while (parent != nullptr && node_ == parent->left)
      {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }

  template < class Key, class Value, class Comparator >
  TreeIterator< Key, Value, Comparator >& TreeIterator< Key,
    Value, Comparator >::operator--(int)
  {
    iter< Key, Value, Comparator > result = *this;
    --(*this);
    return result;
  }

  template < class Key, class Value, class Comparator >
  bool TreeIterator< Key, Value, Comparator >::operator==(const TreeIterator< Key,
    Value, Comparator >& rhs) const
  {
    return node_ == rhs.node_;
  }

  template < class Key, class Value, class Comparator >
  bool TreeIterator< Key, Value, Comparator >::operator!=(const TreeIterator< Key,
    Value, Comparator >& rhs) const
  {
    return !(node_ == rhs.node_);
  }

  template < class Key, class Value, class Comparator >
  const std::pair< Key, Value >& TreeIterator< Key,
    Value, Comparator >::operator*() const
  {
    return node_->data;
  }

  template < class Key, class Value, class Comparator >
  const std::pair< Key, Value >* TreeIterator< Key,
    Value, Comparator >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template < class Key, class Value, class Comparator >
  std::pair< Key, Value >& TreeIterator< Key, Value, Comparator >::operator*()
  {
    return node_->data;
  }

  template < class Key, class Value, class Comparator >
  std::pair< Key, Value >* TreeIterator< Key, Value, Comparator >::operator->() 
  {
    return std::addressof(node_->data);
  }
}

#endif
