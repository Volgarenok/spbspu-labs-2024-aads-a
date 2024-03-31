#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list>

namespace namestnikov
{
  template< class T >
  class Queue
  {
    using queue_t = Queue< T >;
  public:
    Queue() = default;
    ~Queue() = default;
  private:
    std::list< T > data_;
  };
}

#endif