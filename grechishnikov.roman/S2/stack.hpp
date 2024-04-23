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
    Stack(Stack&& other) noexcept;

    ~Stack() = default;

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    void push(const T& other);
    void pop();
    T& top();

    bool empty() const noexcept;
    size_t size() const noexcept;

  private:
    List< T > stack_;
  };

  template< typename T >
  Stack< T >::Stack():
    stack_()
  {}

  template< typename T >
  Stack< T >::Stack(const Stack& other):
    stack_(other.stack_)
  {}

  template< typename T >
  Stack< T >::Stack(Stack&& other) noexcept:
    stack_(std::move(other.stack_))
  {}

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack< T >& other)
  {
    stack_ = other.stack_;
    return *this;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& other) noexcept
  {
    stack_ = std::move(other.stack_);
    return *this;
  }

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
