#ifndef STACK_HPP
#define STACK_HPP

#include "array.hpp"

namespace gladyshev
{
  template < class T, class Container = DynArray< T > >
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
    T drop()
    {
      T temp = array_.front();
      array_.pop_front();
      return temp;
    }
    void push(const T& other)
    {
      array_.push_front(other);
    }
  private:
    Container array_;
  };
}

#endif
