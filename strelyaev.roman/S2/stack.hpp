#ifndef STACK_HPP
#define STACK_HPP
#include "../common/list/list.hpp"

namespace strelyaev
{
  template< typename T >
  class Stack
  {
    public:
      Stack() = default;
      Stack(const Stack< T >&) = default;
      Stack(Stack< T >&&);
      ~Stack() = default;

      void push(const T&);
      T& back();
      const T& back() const;
      T& front();
      const T& front() const;
      bool empty();
      T drop();

      Stack< T >& operator=(const Stack< T >&) = default;
      Stack< T >& operator=(Stack< T >&&);
    private:
      strelyaev::List< T > data;
  };

  template< typename T >
  Stack< T >::Stack(Stack< T >&& other):
    data(std::move(other.data))
  {}

  template< typename T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& other) // no compile
  {
    data = other.data;
  }

  template< typename T >
  void Stack< T >::push(const T& value)
  {
    data.push_back(value);
  }

  template< typename T >
  T& Stack< T >::back()
  {
    return data.back();
  }

  template< typename T >
  const T& Stack< T >::back() const
  {
    return data.back();
  }

  template< typename T >
  T& Stack< T >::front()
  {
    return data.front();
  }

  template< typename T >
  const T& Stack< T >::front() const
  {
    return data.front();
  }

  template< typename T >
  bool Stack< T >::empty()
  {
    return data.empty();
  }

  template< typename T >
  T Stack< T >::drop()
  {
    T value = data.back();
    data.pop_back();
    return value;
  }

}
#endif
