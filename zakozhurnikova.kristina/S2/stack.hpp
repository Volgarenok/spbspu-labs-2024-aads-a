#ifndef STACK_HPP
#define STACK_HPP
#include <list.hpp>

namespace zakozhurnikova
{
  template< class T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack< T >& rhs) = default;
    Stack(Stack< T >&& rhs) noexcept;
    ~Stack() = default;

    Stack< T >& operator=(const Stack< T >&) = default;
    Stack< T >& operator=(Stack< T >&& rhs) noexcept;

    void push(const T& rhs);
    void drop();
    T& top();

  private:
    List< T > stack_;
  };

  template< class T >
 Stack< T >::Stack(Stack< T >&& rhs) noexcept:
    stack_(std::move(rhs.stack_))
  {}

  template< class T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& rhs) noexcept
  {
    if (std::addressof(rhs) != this)
    {
      stack_ = std::move(rhs.stack_);
    }
    return *this;
  }

  template< class T >
  void Stack< T >::push(const T& rhs)
  {
    stack_.push_front(rhs);
  }

  template< class T >
  void Stack< T >::drop()
  {
    stack_.pop_front();
  }

  template< class T >
  T& Stack< T >::top()
  {
    T data = stack_.head->data_;
    return data;
  }
}
#endif
