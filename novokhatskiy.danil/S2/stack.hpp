#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include <forward_list.hpp>

namespace novokhatskiy
{
  template < class T >
  class Stack
  {
  public:

    T& top()
    {
      if (empty())
      {
        throw std::invalid_argument("Stack is empty");
      }
      return data_.front();
    }
    bool empty() const noexcept
    {
      return data_.empty();
    }
    size_t size() const noexcept
    {
      return data_.size();
    }
    void push(const T& value)
    {
      data_.push_front(value);
    }
    void pop()
    {
      data_.pop_front();
    }
  private:
    ForwardList< T > data_;
  };
}

#endif
