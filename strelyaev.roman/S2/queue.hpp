#ifndef QUEUE_HPP
#define QUEUE_HPP

template< typename T >
class Queue
{
  public:
  void push(T rhs);
  T drop();
}

#endif
