#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace gladyshev
{
  template < class T >
  class Queue
  {
  public:
    bool empty() const noexcept
    {
      return list_.empty();
    }
    T& back()
    {
      return list_.back();
    }
    const T& back() const
    {
      return list_.back();
    }
    void pop()
    {
      list_.pop_back();
    }
    void push(const T& other)
    {
      list_.push_front(other);
    }
  private:
    List< T > list_;
  };
}

#endif
