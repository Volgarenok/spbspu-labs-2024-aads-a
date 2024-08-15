#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include "dynamic_array.hpp"

namespace erohin
{
  template< class T, class Container = DynamicArray< T > >
  class Stack
  {
  public:
    Stack();
    template< class InputIt >
    Stack(InputIt first, InputIt last);
    explicit Stack(const Container & cont);
    explicit Stack(Container && cont);
    ~Stack();
    T & top();
    const T & top() const;
    bool empty();
    size_t size();
    void push(const T & value);
    void push(T && value);
    template< class... Args >
    void emplace(Args&&... args);
    void pop();
    void swap(Stack & other) noexcept;
  private:
    Container container_;
  };

  template< class T, class Container >
  Stack< T, Container >::Stack() = default;

  template< class T, class Container >
  template< class InputIt >
  Stack< T, Container >::Stack(InputIt first, InputIt last):
    container_(Container(first, last))
  {}

  template< class T, class Container >
  Stack< T, Container >::Stack(const Container & cont):
    container_(cont)
  {}

  template< class T, class Container >
  Stack< T, Container >::Stack(Container && cont):
    container_(std::move(cont))
  {}

  template< class T, class Container >
  Stack< T, Container >::~Stack() = default;

  template< class T, class Container >
  T & Stack< T, Container >::top()
  {
    return container_.back();
  }

  template< class T, class Container >
  const T & Stack< T, Container >::top() const
  {
    return container_.back();
  }

  template< class T, class Container >
  bool Stack< T, Container >::empty()
  {
    return container_.empty();
  }

  template< class T, class Container >
  size_t Stack< T, Container >::size()
  {
    return container_.size();
  }

  template< class T, class Container >
  void Stack< T, Container >::push(const T & value)
  {
    container_.push_back(value);
  }

  template< class T, class Container >
  void Stack< T, Container >::push(T && value)
  {
    container_.push_back(std::move(value));
  }

  template< class T, class Container >
  template< class... Args >
  void Stack< T, Container >::emplace(Args &&... args)
  {
    container_.emplace_back(std::forward< Args... >(args...));
  }

  template< class T, class Container >
  void Stack<T, Container>::pop()
  {
    container_.pop_back();
  }

  template< class T, class Container >
  void Stack<T, Container>::swap(Stack<T, Container> & rhs) noexcept
  {
    container_.swap(rhs.container_);
  }

  template< class T, class Container >
  void swap(Stack<T, Container> & lhs, Stack<T, Container> & rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template< class T, class Container >
  bool operator==(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs)
  {
    return (lhs.container_ == rhs.container_);
  }

  template< class T, class Container >
  bool operator!=(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs)
  {
    return (lhs.container_ != rhs.container_);
  }

  template< class T, class Container >
  bool operator<(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs)
  {
    return (lhs.container_ < rhs.container_);
  }

  template< class T, class Container >
  bool operator<=(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs)
  {
    return (lhs.container_ <= rhs.container_);
  }

  template< class T, class Container >
  bool operator>(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs)
  {
    return (lhs.container_ > rhs.container_);
  }

  template< class T, class Container >
  bool operator>=(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs)
  {
    return (lhs.container_ >= rhs.container_);
  }
}

#endif
