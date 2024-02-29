#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stdexcept>
#include "node.hpp"

template < class T >
struct Iterator
{
  Node< T > *node;

  Iterator(const Iterator &val):
    node(val.node)
  {}

  Iterator & operator=(const Iterator &val) = default;

  // operator--
  // operator--(int)

  ~Iterator() = default;
  Iterator():
    node(nullptr)
  {}

  Iterator(Node<T> *val):
    node(val)
  {}

  Iterator & operator++()
  {
    if (node == nullptr)
    {
      throw std::logic_error("node == nullptr!");
    }
    node = node->nextNode;
    return *this;
  }

  Iterator operator++(int)
  {
    if (node == nullptr)
    {
      throw std::logic_error("node == nullptr!");
    }
    Iterator res(*this);
    ++(*this);
    return res;
  }

  T &operator*()
  {
    if (node == nullptr)
    {
      throw std::logic_error("node == nullptr");
    }
    return node->value;
  }

  T *operator->()
  {
    if (node == nullptr)
    {
      throw std::logic_error("node == nullptr");
    }
    return std::addressof(*this);
  }


  bool operator!=(const Iterator &val) const
  {
    return node == val.node;
  }

  bool operator==(const Iterator &val) const
  {
    return !(val == *this);
  }
};

#endif
