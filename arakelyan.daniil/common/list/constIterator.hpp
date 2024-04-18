#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <cassert>
#include <memory>
#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct BinList;

  template < class T >
  struct ConstIterator
  {
    friend struct BinList< T >;

    ConstIterator();
    ConstIterator(const ConstIterator< T > &val) = default;
    ~ConstIterator() = default;
    ConstIterator< T > &operator=(const ConstIterator< T > &val) = default;

    ConstIterator< T > &operator--();
    ConstIterator< T > operator--(int);

    ConstIterator< T > operator++();
    ConstIterator< T > operator++(int);

    const T &operator*() const;
    const T *operator->() const;

    bool operator!=(ConstIterator< T > val) const;
    bool operator==(ConstIterator< T > val) const;

  private:
    ConstIterator(details::Node< T > *val);

    using Node = details::Node< T >;
    Node *node;
  };

  template < class T >
  ConstIterator< T >::ConstIterator():
    node(nullptr)
  {}

  template < class T >
  ConstIterator< T >::ConstIterator(details::Node< T > *val):
    node(val)
  {}

  template < class T >
  ConstIterator< T > &ConstIterator< T >::operator--()
  {
    assert(node != nullptr);
    node = node->prevNode;
    return *this;
  }

  template < class T >
  ConstIterator< T > ConstIterator< T >::operator--(int)
  {
    assert(node != nullptr);
    ConstIterator< T > res(*this);
    --(*this);
    return res;
  }

  template < class T >
  ConstIterator< T > ConstIterator< T >::operator++()
  {
    assert(node != nullptr);
    node = node->nextNode;
    return *this;
  }

  template < class T >
  ConstIterator< T > ConstIterator< T >::operator++(int)
  {
    assert(node != nullptr);
    ConstIterator< T > res(*this);
    ++(*this);
    return res;
  }

  template < class T >
  const T &ConstIterator< T >::operator*() const
  {
    assert(node != nullptr);
    return node->value;
  }

  template < class T >
  const T *ConstIterator< T >::operator->() const
  {
    assert(node != nullptr);
    return std::addressof(node->value);
  }

  template < class T >
  bool ConstIterator< T >::operator!=(ConstIterator< T > val) const
  {
    return !(*this == val);
  }

  template < class T >
  bool ConstIterator< T >::operator==(ConstIterator< T > val) const
  {
    return node == val.node;
  }
}
#endif
