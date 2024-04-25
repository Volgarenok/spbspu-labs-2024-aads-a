#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <common/forward_list.hpp>

namespace namestnikov
{
  template< class T >
  class Queue
  {
    using queue_t = Queue< T >;
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
    size_t size()
    {
      return data_.get_size();
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
