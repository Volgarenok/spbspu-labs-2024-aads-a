#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include <list.hpp>

namespace nikitov
{
  template< class T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack< T >& other) = default;
    ~Stack() = default;

    Stack< T >& operator=(const Stack< T >&) = default;

    void push(const T& value);
    T& drop();

  private:
    List< T > data;
  };
}
#endif