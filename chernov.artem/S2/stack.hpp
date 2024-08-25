#ifndef STACK_HPP
#define STACK_HPP
#include "forwardList.hpp"
#include <cstddef>

namespace chernov
{
  template < class T >
  class Stack
  {
  public:
    bool empty()
    {
      return list_.isEmpty();
    }
    size_t size()
    {
      return list_.getSize();
    }
    T& top()
    {
      return list_.front();
    }
    const T& top() const
    {
      return list_.front();
    }
    void pop()
    {
      return list_.pop_front();
    }
    void push(const T& value)
    {
      return list_.push_front(value);
    }
    ~Stack() = default;
  private:
    List< T > list_;
  };
}

#endif
