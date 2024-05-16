#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <bdlist.hpp>

namespace ishmuratov
{
  template< class T >
  class Queue
  {
    public:
      void push(const T & rhs)
      {
        c_.pushFront(rhs);
      }

      void pop()
      {
        c_.popBack();
      }

      T & front() noexcept
      {
        return c_.front();
      }

      const T & front() const noexcept
      {
        return c_.front();
      }

      T & back() noexcept
      {
        return c_.back();
      }

      const T & back() const noexcept
      {
        return c_.back();
      }

      bool empty() const noexcept
      {
        return c_.empty();
      }

      size_t size() const noexcept
      {
        return c_.size();
      }

    private:
      List< T > c_;
  };
}

#endif
