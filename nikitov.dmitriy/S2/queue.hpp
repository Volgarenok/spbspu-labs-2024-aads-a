#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace nikitov
{
  template< class T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue< T >& other) = default;
    ~Queue() = default;

    Queue< T >& operator=(const Queue< T >&) = default;

    void push(const T& value);
    T& drop();

  private:
    List< T > data_;
  };

  template< class T >
  void Queue< T >::push(const T& value)
  {
    data_.push_front(value);
  }

  template< class T >
  T& Queue< T >::drop()
  {
    T value = data_.back();
    data_.pop_back();
    return value;
  }
}
#endif