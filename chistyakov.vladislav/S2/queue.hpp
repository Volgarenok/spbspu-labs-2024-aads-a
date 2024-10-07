#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace chistyakov
{
  template< typename T >
  class Queue
  {
  public:
    T & front() noexcept
    {
      return queue_.front();
    }

    const T & front() const noexcept
    {
      return queue_.front();
    }

    T & back() noexcept
    {
      return queue_.back();
    }

    const T & back() const noexcept
    {
      return queue_.back();
    }

    bool empty() const noexcept
    {
      return queue_.empty();
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
