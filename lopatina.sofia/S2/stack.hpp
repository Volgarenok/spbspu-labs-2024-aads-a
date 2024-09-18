#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace lopatina
{
  template < typename T >
  class Stack
  {
  public:
    bool empty() const
    {
      return stack_list.empty();
    }
    size_t size() const
    {
      return stack_list.size();
    }
    T & top()
    {
      return stack_list.back();
    }
    const T & top() const
    {
      return stack_list.back();
    }
    void push(const T & rhs)
    {
      stack_list.push_back(rhs);
    }
    void pop()
    {
      stack_list.pop_back();
    }
  private:
    List< T > stack_list;
  };
}

#endif
