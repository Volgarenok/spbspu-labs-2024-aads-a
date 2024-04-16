#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>
#include <memory>
#include "node.hpp"

namespace strelyaev
{
  template< typename T >
  class List;

  template< typename T >
  class Iterator
  {
    friend class List< T >;
    public:
     Iterator():
      node_(nullptr)
     {}

     Iterator(const Iterator& val):
      node_(val.node_)
     {}

     ~Iterator() = default;

     Iterator< T >& operator=(Iterator& val) = default;

     Iterator< T > operator++(int)
     {
       Iterator result = *this;
       ++(*this);
       return result;
     }

     Iterator< T >& operator++()
     {
       node_ = node_->next_;
       return *this;
     }

     Iterator< T > operator--(int)
     {
       Iterator< T > result = *this;
       --(*this);
       return result;
     }

     Iterator< T >& operator--()
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

     bool operator==(Iterator< T > val)
     {
       return node_ == val.node_;
     }

     bool operator!=(Iterator< T > val)
     {
       return !(*this == val);
     }

    private:
     detail::Node< T >* node_;

     explicit Iterator(detail::Node< T >* val):
      node_(val)
     {}
  };
}

#endif
