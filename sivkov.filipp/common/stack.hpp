#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace sivkov
{
  template< typename T >
  class Stack
  {
  public:
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const noexcept;
    void swap(Stack< T >& other) noexcept;
  private:
    List< T > list_;
  };

  template< typename T >
  void Stack< T >::push(const T& value)
  {
    list_.push_front(value);
  }

  template< typename T >
  void Stack< T >::pop()
  {
    list_.pop_front();
  }

  template< typename T >
  T& Stack< T >::top()
  {
    return list_.front();
  }

  template< typename T >
  const T& Stack< T >::top() const
  {
    return list_.front();
  }

  template< typename T >
  bool Stack< T >::empty() const noexcept
  {
    return list_.empty();
  }

  template< typename T >
  void Stack< T >::swap(Stack< T >& other) noexcept
  {
    std::swap(list_, other.list_());
  }
}
#endif

