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
    Stack(const Stack< T >& rhs);
    Stack(Stack< T >&& rhs) noexcept;
    ~Stack() = default;

    Stack< T >& operator=(const Stack< T >&);
    Stack< T >& operator=(Stack< T >&& rhs) noexcept;

    void push(const T& rhs);
    void drop();
    T& top() noexcept;
    const T& top() const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    List< T > stack_;
  };

  template< class T >
  Stack< T >::Stack(const Stack< T >& rhs):
    stack_(rhs.stack_)
  {}

  template< class T >
  Stack< T >::Stack(Stack< T >&& rhs) noexcept:
    stack_(std::move(rhs.stack_))
  {}

  template< class T >
  Stack< T >& Stack< T >::operator=(const Stack< T >& rhs)
  {
    if (std::addressof(rhs) != this)
    {
      stack_(rhs.stack_);
    }
  }

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
  T& Stack< T >::top() noexcept
  {
    return stack_.front();
  }

  template< class T >
  const T& Stack< T >::top() const noexcept
  {
    return stack_.front;
  }

  template< class T >
  size_t Stack< T >::size() const noexcept
  {
    return stack_.size();
  }

  template< class T >
  bool Stack< T >::empty() const noexcept
  {
    return stack_.empty();
  }
}
#endif
