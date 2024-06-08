#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace lebedev
{
  template< class T >
  class Queue
  {
  public:
    void push(T rhs);
    T drop();
  };
}

#endif
