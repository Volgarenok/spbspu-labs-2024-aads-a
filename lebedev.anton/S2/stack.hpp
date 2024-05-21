#ifndef STACK_HPP
#define STACK_HPP

namespace lebedev
{
  template< class T >
  class Stack
  {
  public:
    void push(T rhs);
    T drop();
  };
}

#endif
