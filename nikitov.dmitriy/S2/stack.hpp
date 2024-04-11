#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace nikitov
{
  template< class T >
  class Stack
  {
  public:
    T& top();
    void push(const T& value);
    T drop();

    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    List< T > data_;
  };

  template< class T >
  T& Stack< T >::top()
  {
    return data_.front();
  }

  template< class T >
  void Stack< T >::push(const T& value)
  {
    data_.push_front(value);
  }

  template< class T >
  T Stack< T >::drop()
  {
    T value = data_.front();
    data_.pop_front();
    return value;
  }

  template< class T >
  size_t Stack< T >::size() const noexcept
  {
    return data_.size();
  }

  template< class T >
  bool Stack< T >::empty() const noexcept
  {
    return data_.empty();
  }
}
#endif
