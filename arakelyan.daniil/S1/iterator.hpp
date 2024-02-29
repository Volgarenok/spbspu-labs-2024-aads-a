#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stdexcept>
#include "node.hpp"

template < class T >
struct Iterator
{
  Iterator<T>(const Iterator<T> &val) = default;

  Iterator<T> & operator=(const Iterator<T> &val) = default;

  Iterator<T>():
    node(nullptr)
  {}

  Iterator<T>(Node<T> *val):
    node(val)
  {}

  // operator--
  Iterator<T> &operator--()
  {
    node = node->prevNode;
    return *this;
  }
  // operator--(int)
  Iterator<T> operator--(int)
  {
    Iterator<T> res(*this);
    --(*this);
    return res;
  }

  Iterator<T> &operator++()
  {
    if (node == nullptr)
    {
      throw std::logic_error("node == nullptr!");
    }
    node = node->nextNode;
    return *this;
  }

  Iterator<T> operator++(int)
  {
    if (node == nullptr)
    {
      throw std::logic_error("node == nullptr!");
    }
    Iterator<T> res(*this);
    ++(*this);
    return res;
  }

  T &operator*()
  {
    return node->value;
  }

  T *operator->()
  {
    // if (node == nullptr)
    // {
    //   throw std::logic_error("node == nullptr");
    // }
    return std::addressof(*this);
  }

  bool operator!=(const Iterator<T> &val) const
  {
    return node == val.node;
  }

  bool operator==(const Iterator<T> &val) const
  {
    return !(val == *this);
  }

  ~Iterator() = default;

private:
  Node< T > *node;
};

#endif
