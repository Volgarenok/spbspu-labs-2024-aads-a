#ifndef STACK_HPP
#define STACK_HPP
#include <list.hpp>

namespace piyavkin
{
  template< class T >
  class Stack
  {
  public:
    Stack() = default;
    void push(const T& value)
    {
      list.push_back(value);
    }
    void pop()
    {
      list.pop_back();
    }
    bool empty() const
    {
      return list.empty();
    }
  // private:
    List< T > list;
  };
}
#endif