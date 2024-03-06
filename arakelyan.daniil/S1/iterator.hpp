#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stdexcept>
#include <cassert>
#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct Iterator
  {
    Iterator< T >(const Iterator< T > &val) = default;

    Iterator< T > &operator=(const Iterator< T > &val) = default;

    Iterator< T >():
      node(nullptr)
    {}

    Iterator< T >(Node< T > *val):
      node(val)
    {}

    Iterator< T > &operator--()
    {
      assert(node != nullptr);
      node = node->prevNode;
      return *this;
    }

    Iterator< T > operator--(int)
    {
      assert(node != nullptr);
      Iterator< T > res(*this);
      --(*this);
      return res;
    }

    Iterator< T > operator++() // ++a
    {
      assert(node != nullptr);
      node = node->nextNode;
      return *this;
    }

    Iterator< T > operator++(int) // a++
    {
      assert(node != nullptr);
      Iterator< T > res(*this);
      ++(*this);
      return res;
    }

    T &operator*() const
    {
      assert(node != nullptr);
      return node->value;
    }

    T *operator->() const
    {
      assert(node != nullptr);
      return std::addressof(node->value);
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
}
#endif
