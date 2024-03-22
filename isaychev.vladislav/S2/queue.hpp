#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace isaychev
{
  template < class T >
  class Queue
  {
   public:
    void push(T & rhs);
    T drop();
  };

  template < class T >
  void Queue< T >::push(T & rhs)
  {}

  template < class T >
  T Queue< T >::drop()
  {
    T a;
    return a;
  }
}

#endif
