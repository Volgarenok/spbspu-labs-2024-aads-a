#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <memory>
#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct BinList;

  template < class T >
  struct Iterator
  {
    friend struct BinList< T >;

    Iterator();
    Iterator(const Iterator< T > &val) = default;
    ~Iterator() = default;
    Iterator &operator=(const Iterator< T > &val) = default;

    Iterator &operator--();
    Iterator operator--(int);

    Iterator operator++();
    Iterator operator++(int);

    const T &operator*() const;
    T &operator*();
    const T *operator->() const;
    T *operator->();

    bool operator!=(Iterator< T > val) const;
    bool operator==(Iterator< T > val) const;

  private:
    explicit Iterator(details::Node< T > *val);

    using Node = details::Node< T >;
    Node *node;
  };

  template < class T >
  Iterator< T >::Iterator():
    node(nullptr)
  {}

  template < class T >
  Iterator< T >::Iterator(details::Node< T > *val):
    node(val)
  {}

  template < class T >
  Iterator< T > &Iterator< T >::operator--()
  {
    assert(node != nullptr);
    node = node->prevNode;
    return *this;
  }

  template < class T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    assert(node != nullptr);
    Iterator< T > res(*this);
    --(*this);
    return res;
  }

  template < class T >
  Iterator< T > Iterator< T >::operator++()
  {
    assert(node != nullptr);
    node = node->nextNode;
    return *this;
  }

  template < class T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    assert(node != nullptr);
    Iterator< T > res(*this);
    ++(*this);
    return res;
  }

  template < class T >
  const T &Iterator< T >::operator*() const
  {
    assert(node != nullptr);
    return node->value;
  }

  template < class T >
  T &Iterator< T >::operator*()
  {
    assert(node != nullptr);
    return node->value;
  }

  template < class T >
  const T *Iterator< T >::operator->() const
  {
    assert(node != nullptr);
    return std::addressof(node->value);
  }

  template < class T >
  T *Iterator< T >::operator->()
  {
    assert(node != nullptr);
    return std::addressof(node->value);
  }

  template < class T >
  bool Iterator< T >::operator!=(Iterator< T > val) const
  {
    return !(*this == val);
  }

  template < class T >
  bool Iterator< T >::operator==(Iterator< T > val) const
  {
    return node == val.node;
  }
}
#endif
