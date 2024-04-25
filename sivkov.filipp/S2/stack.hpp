#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace sivkov
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack() = default;

    void push(const T& value);
    void pop();
    T& top();
    T drop();
    bool empty() const;
    size_t size() const;
    void swap(Stack< T >& other);

    Stack< T >& operator=(const Stack< T >& other);
    Stack< T >& operator=(Stack< T >&& other) noexcept;

  private:
    List< T > list_;
  };

  template< typename T >
  Stack< T >::Stack() :
    list_()
  {}

  template< typename T >
  Stack< T >::Stack(const Stack& other):
    list_(other.list_)
  {}

  template< typename T >
  Stack< T >::Stack(Stack&& other) noexcept:
    list_(std::move(other.list_))
  {
    other.list_ = list_();
  }

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
  T Stack< T >::drop()
  {
    T data = list_.front();
    list_.pop_front();
    return data;
  }

  template< typename T >
  bool Stack< T >::empty() const
  {
    return list_.empty();
  }

  template< typename T >
  size_t Stack< T >::size() const
  {
    return list_.getSize();
  }

  template< typename T >
  void Stack< T >::swap(Stack< T >& other)
  {
    std::swap(list_, other.list_());
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack< T >& other)
  {
    list_ = other.list_;
    return *this;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& other) noexcept
  {
    list_ = std::move(other.list_);
    other.list_ = list_();
    return *this;
  }
}
#endif
