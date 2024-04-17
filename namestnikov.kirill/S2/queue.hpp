#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list>

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
    size_t size() const noexcept
    {
      return data_.size();
    }
    bool empty() const noexcept
    {
      return data_.empty();
    }
    ~Queue() = default;
  private:
    std::list< T > data_;
  };
}

#endif
