#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace lebedev
{
  template< class T >
  class Stack
  {
  public:
    bool empty() const;
    size_t size() const;

    T & top();
    const T & top() const;

    void push(const T & val);
    void push(T && val);
    void pop();

  private:
    List< T > list_;
  };

  template< class T >
  bool Stack< T >::empty() const
  {
    return list_.empty();
  }
  template< class T >
  size_t Stack< T >::size() const
  {
    return list_.capacity();
  }

  template< class T >
  T & Stack< T >::top()
  {
    return list_.front();
  }
  template< class T >
  const T & Stack< T >::top() const
  {
    return list_.front();
  }

  template< class T >
  void Stack< T >::push(const T & val)
  {
    list_.push_front(val);
  }
  template< class T >
  void Stack< T >::push(T && val)
  {
    list_.push_front(std::move(val));
  }
  template< class T >
  void Stack< T >::pop()
  {
    list_.pop_front();
  }
}

#endif
