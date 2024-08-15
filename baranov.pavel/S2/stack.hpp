#ifndef STACK_HPP
#define STACK_HPP
#include <list/list.hpp>

namespace baranov
{
  template< class T >
  class Stack
  {
  public:
    void push(const T & value);
    void pop();
    T & top();
    const T & top() const;
    bool empty() const noexcept;
    size_t size() const noexcept;
  private:
    List< T > list_;
  };

  template< class T >
  void Stack< T >::push(const T & value)
  {
    list_.push_back(value);
  }

  template< class T >
  void Stack< T >::pop()
  {
    list_.pop_back();
  }

  template< class T >
  T & Stack< T >::top()
  {
    return list_.back();
  }

  template< class T >
  const T & Stack< T >::top() const
  {
    return list_.back();
  }

  template< class T >
  bool Stack< T >::empty() const noexcept
  {
    return list_.empty();
  }

  template< class T >
  size_t Stack< T >::size() const noexcept
  {
    return list_.size();
  }
}
#endif

