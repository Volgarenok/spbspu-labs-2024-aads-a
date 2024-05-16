#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <forward_list.hpp>

namespace namestnikov
{
  template< class T >
  class Queue
  {
  public:
    T & front()
    {
      return data_.front();
    }
    const T & front() const
    {
      return data_.front();
    }
    void push(const T & value)
    {
      data_.push_back(value);
    }
    void pop()
    {
      data_.pop_front();
    }
    bool empty() const noexcept
    {
      return data_.empty();
    }
    ~Queue() = default;
  private:
    ForwardList< T > data_;
  };
}

#endif
