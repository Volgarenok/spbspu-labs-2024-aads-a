#ifndef LISTITERATOT_HPP
#define LISTITERATOR_HPP
#include <memory>
#include "node.hpp"

namespace piyavkin
{
  template< class D >
  class ListIterator
  {
  public:
    ListIterator():
      node(nullptr)
    {}
    ListIterator(const ListIterator< D >&) = default;
    ListIterator< D >& operator=(const ListIterator< D >&) = default;
    ~ListIterator() = default;
    ListIterator< D >& operator++()
    {
      node = node->next_;
      return *this;
    }
    ListIterator< D >& operator--()
    {
      node = node->prev_;
      return *this;
    }
    ListIterator< D > operator++(int)
    {
      ListIterator< D > result(*this);
      ++(*this);
      return result;
    }
    ListIterator< D > operator--(int)
    {
      ListIterator< D > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const ListIterator< D >& rhs) const
    {
      return node == rhs.node;
    }
    bool operator!=(const ListIterator< D >& rhs) const
    {
      return !(*this == rhs);
    }
    D* operator->()
    {
      return std::addressof(node->value_);
    }
    D& operator*()
    {
      return node->value_;
    }
    Node< D >* node;
  };
}
#endif
