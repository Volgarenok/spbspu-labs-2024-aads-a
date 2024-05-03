#ifndef CONST_ITERATORS_HPP
#define CONST_ITERATORS_HPP

#include "node.hpp"

namespace skuratov
{
  template< typename T >
  class List;

  template< typename T >
  class ConstIterator
  {
    public:
      ConstIterator():
        nodePointer(nullptr)
      {}
      ~ConstIterator() = default;
      ConstIterator(const ConstIterator< T >&) = default;

      const T& operator*() const
      {
        return nodePointer->value_;
      }
      const T* operator->() const
      {
        return &(nodePointer->value_);
      }

      bool operator==(const ConstIterator< T >& diff) const
      {
        return nodePointer == diff.nodePointer;
      }
      bool operator!=(const ConstIterator< T >& diff) const
      {
        return nodePointer != diff.nodePointer;
      }

      ConstIterator< T >& operator=(const ConstIterator< T >&) = default;
      ConstIterator< T >& operator++()
      {
        nodePointer = nodePointer->next;
        return *this;
      }
      ConstIterator< T >& operator--()
      {
        nodePointer = nodePointer->prev;
        return *this;
      }
      ConstIterator< T > operator++(int)
      {
        ConstIterator< T > result(*this);
        (*this)++;
        return result;
      }
      ConstIterator< T > operator--(int)
      {
        ConstIterator< T > result(*this);
        (*this)--;
        return result;
      }

    private:
      friend List< T >;
      detail::Node< T >* nodePointer;
      explicit ConstIterator(detail::Node< T >* nodePointer_) :
        nodePointer(nodePointer_)
      {}
  };
}

#endif
