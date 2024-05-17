#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <forward_list.hpp>
#include "tokens.hpp"

namespace novokhatskiy
{
  template < class T >
  class Queue
  {
  public:
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
