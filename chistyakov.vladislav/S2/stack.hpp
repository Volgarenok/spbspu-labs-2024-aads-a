#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace chistyakov
{
  template< typename T >
  class Stack
  {
  public:
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

