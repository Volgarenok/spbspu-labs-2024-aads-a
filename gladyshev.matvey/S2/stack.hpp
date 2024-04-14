#ifndef STACK_HPP
#define STACK_HPP

#include "array.hpp"

namespace gladyshev
{
  template < class T, class Container = DynArray< T > >
  class Stack
  {
  public:
    Stack():
      list_(Container())
    {}
    Stack(const Stack& other):
      list_(other.list_)
    {}
    Stack(Stack&& other) noexcept:
      list_(std::move(other.list_))
    {}
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
    T drop()
    {
      T temp = list_.front();
      list_.pop_front();
      return temp;
    }
    void push(const T& other)
    {
      list_.push_front(other);
    }
  private:
    Container list_;
  };
}

#endif
