#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>
#include <memory>
#include "node.hpp"

namespace strelyaev
{
  template< typename T >
  class Iterator
  {
    public:
     Iterator():
      node_(nullptr)
     {}

     Iterator(const Iterator& val):
      node_(val.node_)
     {}

     Iterator(Node< T >* val):
      node_(val)
     {}

     ~Iterator() = default;

     Iterator< T >& operator=(const Iterator& val)
     {
       this->node_ = val.node_;
     }

     Iterator< T > operator++(int)
     {
       Iterator result = *this;
       ++(*this);
       return result;
     }

     Iterator< T >& operator++()
     {
       if (node_ != nullptr)
       {
        node_ = node_->next_;
       }
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
       if (node_ != nullptr)
       {
         node_ = node_->prev_;
       }
       return *this;
     }

     Iterator< T >& operator+(int n)
     {
      Iterator< T > temp(*this);
      for (int a = 0; a < n; a++)
      {
        ++temp;
      }
      return temp;
     }

     Iterator< T >& operator-(int n)
     {
      Iterator< T > temp(*this);
      for (int a = 0; a < n; a--)
      {
        --temp;
      }
      return temp;
     }

     T& operator*()
     {
       return node_->value_;
     }

     T* operator->()
     {
       return std::addressof(node_->value_);
     }

     bool operator==(const Iterator< T >& val)
     {
       return node_ == val.node_;
     }

     bool operator!=(const Iterator< T >& val)
     {
       return !(*this == val);
     }


    private:
     Node< T >* node_;
  };
}

#endif
