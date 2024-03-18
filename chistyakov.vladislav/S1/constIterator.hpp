#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include "biList.hpp"

namespace chistyakov
{
  template< typename T >
  class ConstIterator
  {
    public:
      ConstIterator():
        node_(nullptr)
      {}

      ConstIterator(const ConstIterator & val):
        node_(val.node_)
      {}

      ConstIterator(BiList< T > * val):
        node_(val)
      {}

      ~ConstIterator() = default;

      ConstIterator< T > & operator++()
      {
        if (node_ != nullptr)
        {
          node_ = node_->next;
        }

        return *this;
      }

      ConstIterator< T > & operator++(int)
      {
        ConstIterator< T > now(*this);
        ++(*this);
        return now;
      }

      ConstIterator< T > & operator--()
      {
        if (node_ != nullptr)
        {
          node_ = node_->previous;
        }

        return *this;
      }

      ConstIterator< T > & operator--(int)
      {
        ConstIterator< T > now(*this);
        --(*this);
        return now;
      }

      ConstIterator< T > & operator+(int num)
      {
        ConstIterator< T > now(*this);

        for (int i = 0; i < num; ++i)
        {
          ++now;
        }

        return now;
      }

      ConstIterator< T > & operator-(int num)
      {
        ConstIterator< T > now(*this);

        for (int i = 0; i < num; ++i)
        {
          --now;
        }

        return now;
      }

      bool ConstIterator< T >::operator==(const ConstIterator< T > & rhs) const
      {
        return node_ == rhs.node_;
      }

      bool ConstIterator< T >::operator!=(const ConstIterator< T > & rhs) const
      {
        return !(rhs == *this);
      }

      T & ConstIterator< T >::operator*()
      {
        return node_->value;
      }

      T * ConstIterator< T >::operator->()
      {
        return addressof(node->value);
      }

      BiList< T > * get_BiList()
      {
        return node_;
      }

    private:
      BiList< T > * node_;
  };
}

#endif
