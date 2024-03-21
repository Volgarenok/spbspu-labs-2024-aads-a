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
    void push(const T& value);
    T& drop();

  private:
    List< T > data;
  };
}
#endif