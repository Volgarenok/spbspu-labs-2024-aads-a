#ifndef STACK_HPP
#define STACK_HPP
#include "deque.hpp"
namespace zaitsev
{
  template<typename T>
  class Stack: protected Deque< T >
  {
  public:
    Stack() = default;
    Stack(const Stack& other) = default;
    Stack(Stack&& other) = default;
    ~Stack() = default;
    T& top();
    bool empty() const;
    void push(const T& value);
    void pop();
    void clear();
  };

  template<typename T>
  T& Stack<T>::top()
  {
    return Deque< T >::back();
  }

  template<typename T>
  bool Stack<T>::empty() const
  {
    return Deque<T>::empty();
  }

  template<typename T>
  void Stack<T>::push(const T& value)
  {
    Deque< T >::push_back(value);
  }

  template<typename T>
  void Stack<T>::pop()
  {
    Deque< T >::pop_back();
  }

  template<typename T>
  void Stack<T>::clear()
  {
    Deque< T >::clear();
  }
}
#endif
