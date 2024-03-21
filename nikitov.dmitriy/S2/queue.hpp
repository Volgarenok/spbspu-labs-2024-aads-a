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
}
#endif