#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace zakozhurnikova
{
  template< class T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue< T >& other) = default;
    Queue(Queue< T >&& other) noexcept;
    ~Queue() = default;

    Queue< T >& operator=(const Queue< T >& other) = default;
    Queue< T >& operator=(Queue< T >&& other) noexcept;

  private:
  List< T > data_;
  }

  template< class T >
  Queue< T >::Queue(Queue< T >&& other) noexcept;

  template< class T >
  Queue< T >& Queue< T >::operator=(Queue< T >&& other) noexcept;

}
#endif
