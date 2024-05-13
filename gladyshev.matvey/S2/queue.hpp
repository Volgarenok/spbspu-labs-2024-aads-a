#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "array.hpp"

namespace gladyshev
{
  template < class T >
  class Queue
  {
  public:
    bool empty() const noexcept
    {
      return array_.empty();
    }
    T& back()
    {
      return array_.back();
    }
    const T& back() const
    {
      return array_.back();
    }
    void pop()
    {
      array_.pop_back();
    }
    void push(const T& other)
    {
      array_.push_front(other);
    }
  private:
    DynArray< T > array_;
  };
}

#endif
