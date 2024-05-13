#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include <forward_list.hpp>

namespace novokhatskiy
{
  template < class T >
  class Stack
  {
  public:
    T& top();
    bool empty() const noexcept;
    size_t size() const noexcept;
    void push(const T& value);
    void pop();

  private:
    ForwardList< T > data_;
  };

  template < class T >
  T& Stack< T >::top()
  {
    if (empty())
    {
      throw std::invalid_argument("Stack is empty");
    }
    return data_.front();
  }

  template < class T >
  bool Stack< T >::empty() const noexcept
  {
    return data_.empty();
  }

  template < class T >
  size_t Stack< T >::size() const noexcept
  {
    return data_.size();
  }

  template < class T >
  void Stack< T >::push(const T& value)
  {
    data_.push_front(value);
  }

  template < class T >
  void Stack< T >::pop()
  {
    data_.pop_front();
  }

  template < class T >
  Stack< T >::Stack(Stack< T >&& other) noexcept:
    data_(std::move(other.data))
  {}

  template < class T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& other) noexcept
  {
    if (std::addressof(other) != this)
    {
      std::swap(data_, other.data_);
      other.data_.clear();
    }
    return *this;
  }
}

#endif
