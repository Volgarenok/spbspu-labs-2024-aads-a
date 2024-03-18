#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "biList.hpp"

namespace chistyakov
{
  template< typename T >
  class Iterator
  {
    public:
      Iterator():
        node_(nullptr)
      {}

      Iterator(const Iterator & val):
        node_(val)
      {}

      ~Iterator() = default;
      Iterator(const Iterator< T > & ) = default;
      Iterator< T > & operator=(const Iterator< T > & ) = default;

      Iterator< T > & operator++()
      {
        if (node_ != nullptr)
        {
          node_ = node_->next_;
        }

        return *this;
      }

      Iterator< T > & operator++(int)
      {
        Iterator now(*this);
        ++(*this);
        return now;
      }

      Iterator< T > & operator--()
      {
        if (node_ != nullptr)
        {
          node_ = node_->previous_;
        }

        return *this;
      }

      Iterator< T > & operator--(int)
      {
        Iterator now(*this);
        --(*this);
        return now;
      }

      bool Iterator< T >::operator==(const Iterator< T > & rhs) const
      {
        return node_ == rhs.node_;
      }

      bool Iterator< T >::operator!=(const Iterator< T > & rhs) const
      {
        return !(rhs == *this);
      }

      T & Iterator< T >::operator*()
      {
        return node_->value;
      }

      T * Iterator< T >::operator->()
      {
        return addressof(node->value);
      }


    private:
      BiList< T > * node_;
  };
}

#endif
