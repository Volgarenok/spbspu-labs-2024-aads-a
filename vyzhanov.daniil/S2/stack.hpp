#ifndef STACK_HPP
#define STACK_HPP

#include </Users/Daniil/source/repos/fwd_list/fwd_list/List.hpp>

namespace vyzhanov
{
  template < typename T >
  class Stack
  {
  public:
    void push(const T&);
    void pop();
    bool empty() const noexcept;
    size_t capacity() const noexcept;
    T& top();
    const T& top() const;
    void swap(Stack< T >&);
  private:
    List< T > stack_;
  };

  template < typename T >
  void Stack< T >::push(const T& obj)
  {
    stack_.push_back(obj);
  }

  template < typename T >
  void Stack< T >::pop()
  {
    stack_.pop_back();
  }

  template < typename T >
  bool Stack< T >::empty() const noexcept
  {
    return stack_.empty();
  }

  template < typename T >
  size_t Stack< T >::capacity() const noexcept
  {
    return stack_.capacity();
  }

  template< typename T>
  T& Stack<T>::top()
  {
    return stack_.back();
  }

  template< typename T>
  const T& Stack<T>::top() const
  {
    return stack_.back();
  }

  template< typename T>
  void Stack<T>::swap(Stack< T >& newStack)
  {
    stack_.swap(newStack);
  }
}

#endif
