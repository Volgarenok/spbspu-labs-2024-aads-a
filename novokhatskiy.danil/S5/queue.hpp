#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "forward_list.hpp"

namespace novokhatskiy
{
  template < typename T >
  class Queue
  {
  public:
      bool operator==(const Queue< T >& other) const
      {
        return data_ == other.data_;
      }
      bool operator!=(const Queue< T >& other) const
      {
        return data_ != other.data_;
      }

      void push(const T& value)
      {
        data_.push_back(value);
      }
      bool empty() const noexcept
      {
        return data_.empty();
      }
      size_t size() const noexcept
      {
        return data_.size();
      }
      void pop()
      {
        data_.pop_front();
      }
      T& front()
      {
        if (empty())
        {
          throw std::invalid_argument("Queue is empty");
        }
        return data_.front();
      }
  private:
      ForwardList< T > data_;
  };
}

#endif
