#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include <list.hpp>

namespace nikitov
{
  template< class T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack< T >& other) = default;
    ~Stack() = default;

    Stack< T >& operator=(const Stack< T >&) = default;

    void push(const T& value);
    T& drop();

    size_t size() const;
    bool empty() const;

  private:
    List< T > data;
  };

  template< class T >
  void Stack< T >::push(const T& value)
  {
    data.push_front(value);
  }

  template< class T >
  T& Stack< T >::drop()
  {
    T value = data.front();
    data.pop_front();
    return value;
  }

  template< class T >
  size_t Stack< T >::size() const
  {
    return data.size();
  }

  template< class T >
  bool Stack< T >::empty() const
  {
    return data.empty();
  }
}
#endif