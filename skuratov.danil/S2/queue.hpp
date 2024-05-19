#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace skuratov
{
  template< typename T >
  class Queue
  {
  public:
    void push(const T& diff)
    {
      queue_.pushFront(diff);
    }
    void drop()
    {
      queue_.popBack();
    }
    bool empty() const noexcept
    {
      return queue_.empty();
    }
    size_t size() const noexcept
    {
      return queue_.getSize();
    }
    T& top() noexcept
    {
      return queue_.back();
    }
    const T& top() const noexcept
    {
      return queue_.back();
    }
    T& front() noexcept
    {
      return queue_.front();
    }
    const T& front() const noexcept
    {
      return queue_.front();
    }
  private:
    List< T > queue_;
  };
}

#endif
