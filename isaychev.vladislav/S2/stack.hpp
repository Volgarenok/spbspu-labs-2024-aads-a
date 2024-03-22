#ifndef STACK_HPP
#define STACK_HPP

namespace isaychev
{
  template < class T >
  class Stack
  {
   public:
    void push(T & rhs);
    T drop();
  };

  template < class T >
  void Stack< T >::push(T & rhs)
  {}

  template < class T >
  T Stack< T >::drop()
  {
    T a;
    return a;
  }
}

#endif
