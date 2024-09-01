#ifndef TREECONSTITERATOR_HPP
#define TREECONSTITERATOR_HPP

#include "TreeNode.hpp"
#include <functional>
#include <iterator>
#include <utility>

namespace vyzhanov
{

  template < class Key, class Value, class Comparator >
  class AVLTree;

  template < class Key, class Value, class Comparator = std::less< Key > >
  struct TreeConstIterator: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
    friend class AVLTree< Key, Value, Comparator >;
    using citerator = TreeConstIterator< Key, Value, Comparator >;
    using TreeNode = detail::TreeNode< Key, Value >;
    using pair = std::pair< Key, Value >;

    TreeConstIterator();
    TreeConstIterator(const citerator&) = default;
    ~TreeConstIterator() = default;
    citerator& operator=(const TreeConstIterator< Key, Value, Comparator >&) = default;
    citerator& operator=(TreeConstIterator< Key, Value, Comparator >&&) = default;
    citerator& operator++();
    citerator& operator++(int);
    citerator& operator--();
    citerator& operator--(int);
    bool operator==(const TreeConstIterator< Key, Value, Comparator >&) const;
    bool operator!=(const TreeConstIterator< Key, Value, Comparator >&) const;
    const pair& operator*() const;
    const pair* operator->() const;

  private:
    TreeNode* node_;
    TreeConstIterator(TreeNode* node);
  };

  template < class Key, class Value, class Comparator >
  TreeConstIterator< Key, Value, Comparator >::TreeConstIterator():
    node_(nullptr)
  {}

  template < class Key, class Value, class Comparator >
  TreeConstIterator< Key, Value, Comparator >::TreeConstIterator(TreeNode* node):
    node_(node)
  {}

  template < class Key, class Value, class Comparator >
  TreeConstIterator< Key, Value, Comparator >& TreeConstIterator< Key,
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
  TreeConstIterator< Key, Value, Comparator >& TreeConstIterator< Key,
    Value, Comparator >::operator++(int)
  {
    iter< Key, Value, Comparator > result = *this;
    ++(*this);
    return result;
  }

  template < class Key, class Value, class Comparator >
  TreeConstIterator< Key, Value, Comparator >& TreeConstIterator< Key,
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
  TreeConstIterator< Key, Value, Comparator >& TreeConstIterator< Key,
    Value, Comparator >::operator--(int)
  {
    iter< Key, Value, Comparator > result = *this;
    --(*this);
    return result;
  }

  template < class Key, class Value, class Comparator >
  bool TreeConstIterator< Key, Value, Comparator >::operator==(const
    TreeConstIterator< Key, Value, Comparator >& rhs) const
  {
    return node_ == rhs.node_;
  }

  template < class Key, class Value, class Comparator >
  bool TreeConstIterator< Key, Value, Comparator >::operator!=(const 
    TreeConstIterator< Key, Value, Comparator >& rhs) const
  {
    return !(node_ == rhs.node_);
  }

  template < class Key, class Value, class Comparator >
  const std::pair< Key, Value >& TreeConstIterator< Key,
    Value, Comparator >::operator*() const
  {
    return node_->data;
  }

  template < class Key, class Value, class Comparator >
  const std::pair< Key, Value >* TreeConstIterator< Key,
    Value, Comparator >::operator->() const
  {
    return std::addressof(node_->data);
  }
}

#endif
