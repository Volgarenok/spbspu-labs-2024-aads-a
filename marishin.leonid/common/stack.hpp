#ifndef STACK_HPP
#define STACK_HPP

#include <linkedList.hpp>

namespace marishin
{
  template< class T >
  class Stack
  {
  public:
    void push(const T& rhs);
    void drop();
    T& top() noexcept;
    const T& top() const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
  private:
    LinkedList< T > stack_;
  };

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
    return stack_.front();
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
