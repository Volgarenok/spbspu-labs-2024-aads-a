#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP
#include <iterator>
#include <functional>
#include <utility>
#include "treeNode.hpp"

namespace zakozhurnikova
{
  template <class Key, class Value, class Compare>
  class BinarySearchTree;

  template <class Key, class Value, class Compare = std::less< Key > >
  struct ConstIterator: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
      friend class BinarySearchTree<Key, Value, Compare>;
      using this_t = ConstIterator<Key, Value, Compare>;
      using TreeNode = detail::TreeNode<Key, Value>;

      ConstIterator() = default;
      ConstIterator(detail::TreeNode< Key, Value >* node):
        node_(node)
      {}
      this_t &operator=(const this_t &) = default;
      this_t &operator++();
      this_t operator++(int);
      this_t &operator--();
      this_t operator--(int);
      bool operator!=(const this_t &) const;
      bool operator==(const this_t &) const;
      const std::pair< Key, Value >& operator*() const;
      const std::pair< Key, Value >* operator->() const;

  private:
      detail::TreeNode< Key, Value >* node_;
  };

  template <class Key, class Value, class Compare>
  ConstIterator< Key, Value, Compare >& ConstIterator<Key, Value, Compare>::operator++()
  {
     if (node_->rightChild)
    {
      node_ = node_->rightChild;
      while (node_->leftChild)
      {
        node_ = node_->leftChild;
      }
      return *this;
    }
    while (node_->parent && node_->parent->rightChild == node_)
    {
      node_ = node_->parent;
    }
    node_ = node_->parent;
    return *this;
  }

  template < class Key, class Value, class Compare >
  ConstIterator<Key, Value, Compare> ConstIterator<Key, Value, Compare>::operator++(int)
  {
      ConstIterator<Key, Value> result(*this);
      ++(*this);
      return result;
  }

  template < class Key, class Value, class Compare >
  ConstIterator<Key, Value, Compare> &ConstIterator<Key, Value, Compare>::operator--()
  {
      node_ = node_->prev;
      return *this;
  }

  template < class Key, class Value, class Compare >
  ConstIterator<Key, Value, Compare> ConstIterator<Key, Value, Compare>::operator--(int)
  {
      ConstIterator<Key, Value, Compare> result(*this);
      --(*this);
      return result;
  }

  template < class Key, class Value, class Compare >
  bool ConstIterator< Key, Value, Compare >::operator==(const ConstIterator<Key, Value, Compare> &rhs) const
  {
      return node_ == rhs.node_;
  }

  template < class Key, class Value, class Compare >
  bool ConstIterator<Key, Value, Compare>::operator!=(const ConstIterator<Key, Value, Compare> &rhs) const
  {
      return !(*this == rhs);
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value >& ConstIterator< Key, Value, Compare >::operator*() const
  {
      return node_->data;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value >* ConstIterator< Key, Value, Compare >::operator->() const
  {
      return std::addressof(node_->data);
  }
}

#endif
