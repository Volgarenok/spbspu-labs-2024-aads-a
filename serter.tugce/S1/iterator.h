#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <cstddef>
#include <stdexcept>

namespace serter
{

  template < typename T >

  class Iterator
  {
  public:
    Iterator();
    Iterator(Node< T >* node) : current_(node)
    {}

    Iterator< T >& operator++()
    {
      if(current_)
      {
        current_ = current_->next_;
      }
      return *this;
    }

    Iterator<T>& operator--()
    {
      if(current_)
      {
        current_ = current_->prev_;
      }

      return *this;
    }

    Iterator< T >& operator+(size_t n)
    {
      Iterator< T > temp = *this;
      for (size_t i = 0; i < n; ++i)
      {
        ++temp;
      }
      return temp;
    }

    Iterator< T >& operator-(size_t n)
    {
      Iterator< T > temp = *this;
      for (size_t i = 0; i < n; ++i)
      {
        --temp;
      }
      return temp;
    }

    bool operator==(const Iterator< T >& obj) const
    {
      return current_ == obj.current_;
    }

    bool operator!=(const Iterator< T >& obj) const
    {
      return current_ != obj.current_;
    }

    T& operator*() const
    {
      return current_->data_;
    }

    T* operator->() const
    {
      return &(current_->data_);
    }

  private:
    Node< T >* current_;
  };

}

#endif


