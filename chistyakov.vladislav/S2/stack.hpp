#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace chistyakov
{
  template< typename T >
  class Stack
  {
  public:
    T & top() noexcept
    {
      return stack_.back();
    }

    const T & top() const noexcept
    {
      return stack_.back();
    }

    bool empty() const noexcept
    {
      return stack_.empty();
    }

    void push(const T & value)
    {
      stack_.push_back(value);
    }

    void pop()
    {
      stack_.pop_back();
    }
  private:
    List< T > stack_;
  }
}

#endif

