#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <cassert>
#include <memory>
#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct ConstIterator
  {

    ConstIterator< T >(const ConstIterator< T > &val) = default;

    ConstIterator< T > &operator=(const ConstIterator< T > &val) = default;

    ConstIterator< T >():
      node(nullptr)
    {}

    ConstIterator< T >(const Node< T > *val):
      node(val)
    {}

    ConstIterator< T > &operator--()
    {
      assert(node != nullptr);
      node = node->prevNode;
      return *this;
    }

    ConstIterator< T > operator--(int)
    {
      assert(node != nullptr);
      ConstIterator< T > res(*this);
      --(*this);
      return res;
    }

    ConstIterator< T > operator++() // ++a
    {
      assert(node != nullptr);
      node = node->nextNode;
      return *this;
    }

    ConstIterator< T > operator++(int) // a++
    {
      assert(node != nullptr);
      ConstIterator< T > res(*this);
      ++(*this);
      return res;
    }

    const T &operator*() const
    {
      assert(node != nullptr);
      return node->value;
    }

    const T *operator->() const
    {
      assert(node != nullptr);
      return std::addressof(node->value);
    }

    bool operator!=(const ConstIterator< T > &val) const
    {
      return !(*this == val);
    }

    bool operator==(const ConstIterator< T > &val) const
    {
      return node == val.node;
    }

    ~ConstIterator() = default;

  private:
    const Node< T > *node;
  };
}

#endif
