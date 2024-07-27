#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace chistyakov
{
  template< typename T >
  class Queue
  {
  public:
    T & front()
    {
      return queue_.front();
    }

    T & back()
    {
      return queue_.back();
    }

    void push(const T & value)
    {
      queue_.push_back(value);
    }

    void pop()
    {
      queue_.pop_front();
    }

  private:
    List< T > queue_;
  };
}

#endif
