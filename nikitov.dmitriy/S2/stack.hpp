#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace nikitov
{
  template< class T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack< T >& other) = default;
    Stack(Stack< T >&& other) noexcept;
    ~Stack() = default;

    Stack< T >& operator=(const Stack< T >&) = default;
    Stack< T >& operator=(Stack< T >&& other) noexcept;

    T& top();
    void push(const T& value);
    T drop();

    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    List< T > data_;
  };

  template< class T >
  Stack< T >::Stack(Stack< T >&& other) noexcept:
    data_(std::move(other.data_))
  {}

  template< class T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& other) noexcept
  {
    if (std::addressof(other) != this)
    {
      std::swap(data_, other.data_);
      other.data_.clear();
    }
    return *this;
  }

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
