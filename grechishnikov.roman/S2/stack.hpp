#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace grechishnikov
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other);

    ~Stack() = default;

    void push(const T& other);
    void pop();
    T& top();
  private:
    List< T > stack;
  };

  template< typename T >
  Stack< T >::Stack():
    stack()
  {}

  template< typename T >
  void Stack< T >::push(const T& other)
  {
    stack.push_front(other);
  }

  template< typename T >
  void Stack< T >::pop()
  {
    stack.pop_front();
  }

  template< typename T >
  T& Stack< T >::top()
  {
    return *stack.begin();
  }
}

#endif
