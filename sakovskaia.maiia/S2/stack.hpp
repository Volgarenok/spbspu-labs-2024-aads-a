#ifndef STACK_HPP
#define STACK_HPP
#include <list.hpp>

namespace sakovskaia
{
  template< typename T >
  class Stack
  {
  public:
    void push_back(const T & value);
    T & front() noexcept;
    const T & front() const noexcept;
    bool empty() const noexcept;
  private:
    List< T > data;
  };

  template< typename T >
  void Stack< T >::push_back(const T & value)
  {
    data.push_back(value);
  }

  template< typename T >
  T & Stack< T >::front() noexcept
  {
    return data.front();
  }

  template< typename T >
  const T & Stack< T >::front() const noexcept
  {
    return data.front();
  }

  template< typename T >
  bool Stack< T >::empty() const noexcept
  {
    return data.empty();
  }
}

#endif
