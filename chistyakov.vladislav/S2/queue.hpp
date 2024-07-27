#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace chistyakov
{
  template< typename T >
  class Queue
  {
  public:
    void push(const T & value)
    {
      queue_.push_back;
    }

    void pop()
    {
      queue_.pop_front();
    }

  private:
    List< T > queue_;
  }
}

#endif
