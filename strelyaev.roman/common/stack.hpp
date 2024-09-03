#ifndef STACK_HPP
#define STACK_HPP
#include <list/list.hpp>

namespace strelyaev
{
  template< typename T >
  class Stack
  {
    public:
      void push(const T&);
      T& back();
      const T& back() const;
      T& front();
      const T& front() const;
      bool empty();
      void pop_back();

    private:
      List< T > data;
  };

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
  void Stack< T >::pop_back()
  {
    data.pop_back();
  }
}
#endif


