#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include "node.hpp"

template <typename Key, typename Value>
struct ConstIterator
{
  using node = Node<Key, Value>;
  using pointer = const node*;
  using reference = const node&;

  ConstIterator(pointer ptr):
    ptr_(ptr)
  {}

  ConstIterator& operator++()
  {
    ptr_ = successor(ptr_);
    return *this;
  }

  ConstIterator operator++(int)
  {
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  bool operator==(const ConstIterator& other) const
  {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(*this == other);
  }

  reference operator*() const
  {
    return *ptr_;
  }

  pointer operator->() const
  {
    return ptr_;
  }

private:
  pointer ptr_;

  pointer successor(pointer node) const
  {
    if (node->right != nullptr)
    {
      node = node->right;
      while (node->left != nullptr)
      {
        node = node->left;
      }
      return node;
    }
    else
    {
      pointer parent = node->parent;
      while (parent != nullptr && node == parent->right)
      {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  }
};

#endif

