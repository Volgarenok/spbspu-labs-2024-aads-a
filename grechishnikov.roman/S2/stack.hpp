#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace grechishnikov
{
  template< typename T >
  class Stack
  {
  public:
    void push(const T& other);
    void pop();
    T& top();
    const T& top() const;

    bool empty() const noexcept;
    size_t size() const noexcept;

  private:
    List< T > stack_;
  };

  template< typename T >
  void Stack< T >::push(const T& other)
  {
    stack_.push_front(other);
  }

  template< typename T >
  void Stack< T >::pop()
  {
    stack_.pop_front();
  }

  template< typename T >
  T& Stack< T >::top()
  {
    return *stack_.begin();
  }

  template< typename T >
  const T& Stack< T >::top() const
  {
    return *stack_.begin();
  }

  template< typename T >
  bool Stack< T >::empty() const noexcept
  {
    return stack_.empty();
  }

  template< typename T >
  size_t Stack< T >::size() const noexcept
  {
    return stack_.size();
  }
}

#endif
