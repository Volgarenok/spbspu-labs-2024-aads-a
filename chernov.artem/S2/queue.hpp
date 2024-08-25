#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <common/forwardList.hpp>
#include <cstddef>

namespace chernov
{
  template < class T >
  class Queue
  {
  public:
    bool empty()
    {
      return list_.isEmpty();
    }
    size_t size()
    {
      return list_.getSize();
    }
    T& front()
    {
      return list_.front();
    }
    const T& front() const
    {
      return list_.front();
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
      return list_.pop_back();
    }
    void push(const T& value)
    {
      return list_.push_front(value);
    }
    ~Queue() = default;
  private:
    List< T > list_;
  };
}

#endif
