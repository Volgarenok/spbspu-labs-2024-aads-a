#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP
#include <cstddef>
#include <memory>
#include "node.hpp"

namespace strelyaev
{
  template< typename T >
  class List;

  template< typename T >
  class ConstIterator
  {
    friend class List< T >;
    public:
      ConstIterator():
        node_(nullptr)
       {}

      ConstIterator(const ConstIterator& val):
        node_(val.node_)
       {}

      ~ConstIterator() = default;

      ConstIterator< T >& operator++()
      {
        node_ = node_->next_;
        return *this;
      }

      ConstIterator< T > operator++(int)
      {
        ConstIterator< T > result(*this);
        ++(*this);
        return result;
      }

     ConstIterator< T > operator--(int)
     {
       ConstIterator< T > result = *this;
       --(*this);
       return result;
     }

     ConstIterator< T >& operator--()
     {
       node_ = node_->prev_;
       return *this;
     }

      T& operator*()
      {
        return node_->value_;
      }

      T* operator->()
      {
        return std::addressof(node_->value_);
      }

      bool operator==(ConstIterator< T > val) const
      {
        return node_ == val.node_;
      }

      bool operator!=(ConstIterator< T > val) const
      {
        return !(*this == val);
      }

    private:
      detail::Node< T >* node_;

      explicit ConstIterator(detail::Node< T >* val):
       node_(val)
      {}
  };
}
#endif
