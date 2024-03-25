#ifndef STACK_HPP
#define STACK_HPP
#include "deque.hpp"
namespace zaitsev
{
  template<typename T>
  class Stack: private Deque< T >
  {
  public:
    using iterator = Deque<T>::iterator;
    using const_iterator = Deque<T>::const_iterator;

    T& top()
    {
      return Deque< T >::back();
    }
    bool empty() const
    {
      return Deque<T>::empty();
    }
    void push(const T& value)
    {
      Deque< T >::push_back(value);
    }
    void pop()
    {
      Deque< T >::pop_back();
    }
    void clear()
    {
      Deque< T >::clear();
    }
    iterator begin()
    {
      return Deque<T>::begin();
    }
    iterator end()
    {
      return Deque<T>::end();
    }
    const_iterator begin() const
    {
      return Deque<T>::cbegin();
    }
    const_iterator end() const
    {
      return Deque<T>::cend();
    }
    const_iterator cbegin() const
    {
      return Deque<T>::cbegin();
    }
    const_iterator cend() const
    {
      return Deque<T>::cend();
    }
  };
}
#endif
