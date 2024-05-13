#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace gladyshev
{
  template < class T >
  class Stack
  {
  public:
    T& top()
    {
      return list_.front();
    }
    const T& top() const
    {
      return list_.front();
    }
    bool empty() const noexcept
    {
      return list_.empty();
    }
    void pop()
    {
      list_.pop_front();
    }
    void push(const T& other)
    {
      list_.push_front(other);
    }
  private:
    List< T > list_;
  };
}

#endif
