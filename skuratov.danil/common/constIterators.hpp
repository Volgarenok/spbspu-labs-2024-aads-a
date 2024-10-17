#ifndef CONST_ITERATORS_HPP
#define CONST_ITERATORS_HPP

#include <memory>
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
        nodePointer_(nullptr)
      {}
      ~ConstIterator() = default;
      ConstIterator(const ConstIterator< T >&) = default;

      const T& operator*() const
      {
        return nodePointer_->value_;
      }
      const T* operator->() const
      {
        return std::addressof(nodePointer_->value_);
      }

      bool operator==(const ConstIterator< T >& diff) const
      {
        return nodePointer_ == diff.nodePointer_;
      }
      bool operator!=(const ConstIterator< T >& diff) const
      {
        return nodePointer_ != diff.nodePointer_;
      }

      ConstIterator< T >& operator=(const ConstIterator< T >&) = default;
      ConstIterator< T >& operator++()
      {
        nodePointer_ = nodePointer_->next_;
        return *this;
      }
      ConstIterator< T >& operator--()
      {
        nodePointer_ = nodePointer_->prev_;
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
      detail::Node< T >* nodePointer_;
      explicit ConstIterator(detail::Node< T >* nodePointer):
        nodePointer_(nodePointer)
      {}
  };
}

#endif
