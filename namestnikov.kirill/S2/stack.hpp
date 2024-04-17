#ifndef STACK_HPP
#define STACK_HPP

#include <list>
#include <cstddef>
#include "forward_list.hpp"

namespace namestnikov
{
  template< class T >
  class Stack
  {
    using stack_t = Stack< T >;
  public:
    void push(const T & value)
    {
      data_.push_front(value);
    }
    void pop()
    {
      data_.pop_front();
    }
    T & top()
    {
      return data_.front();
    }
    const T & top() const
    {
      return data_.front();
    }
    size_t size()
    {
      return data_.get_size();
    }
    bool empty() const noexcept
    {
      return data_.empty();
    }
    ~Stack() = default;
  private:
    ForwardList< T > data_;
  };
}

#endif
