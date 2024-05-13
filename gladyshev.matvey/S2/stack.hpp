#ifndef STACK_HPP
#define STACK_HPP

#include "array.hpp"

namespace gladyshev
{
  template < class T >
  class Stack
  {
  public:
    T& top()
    {
      return array_.front();
    }
    const T& top() const
    {
      return array_.front();
    }
    bool empty() const noexcept
    {
      return array_.empty();
    }
    void pop()
    {
      array_.pop_front();
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
