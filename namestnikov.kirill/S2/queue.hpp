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
    ~Queue() = default;
  private:
    std::list< T > data_;
  };
}

#endif