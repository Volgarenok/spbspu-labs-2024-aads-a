#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stdexcept>
#include "node.hpp"

template < class T >
struct Iterator
{
  Iterator<T>(const Iterator< T > &val) = default;

  Iterator<T> &operator=(const Iterator< T > &val) = default;

  Iterator< T >():
    node(nullptr)
  {}

  Iterator< T >(Node< T > *val) :
    node(val)
  {}

  // operator--
  Iterator< T > &operator--()
  {
    node = node->prevNode;
    return *this;
  }

  // operator--(int)
  Iterator< T > operator--(int)
  {
    Iterator< T > res(*this);
    --(*this);
    return res;
  }

  Iterator< T > operator++() // ++a
  {
    node = node->nextNode;
    return *this;
  }

  Iterator< T > operator++(int) // a++
  {
    Iterator< T > res(*this);
    ++(*this);
    return res;
  }

  T &operator*() // + const ver
  {
    return node->value;
  }

  T *operator->() // + const ver
  {
    return std::addressof(*this);
  }

  bool operator!=(const Iterator< T > &val) const
  {
    return !(*this == val); 
  }

  bool operator==(const Iterator< T > &val) const
  {
    return node == val.node;
  }

  ~Iterator() = default;

private:
  Node< T > *node;
};

#endif
