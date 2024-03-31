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
    Queue() = default;
    Queue(const queue_t & other) = default;
    queue_t & operator=(const queue_t & other) = default;
    Queue(queue_t && other) noexcept:
      data_(std::move(other.data_))
    {}
    queue_t & operator=(queue_t && other)
    {
      if (std::addressof(other) != this)
      {
        std::swap(data_, other.data_);
      }
      return *this;
    }
    T & front() const noexcept
    {
      return data_.front();
    }
    T & back() const noexcept
    {
      return data_.back();
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