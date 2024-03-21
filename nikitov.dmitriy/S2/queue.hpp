#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "stack.hpp"

namespace nikitov
{
  template< class T >
  class Queue
  {
  public:
    void push(const T& value);
    T& drop();
  private:
    List< T > data_;
  };
}
#endif