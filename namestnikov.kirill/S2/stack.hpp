#ifndef STACK_HPP
#define STACK_HPP

#include <list>
#include <iostream>

namespace namestnikov
{
  template< class T >
  class Stack
  {
    using stack_t = Stack< T >;
  public:
    Stack() = default;
    Stack(const stack_t & other) = default;
    stack_t & operator=(const stack_t & other) = default;
    Stack(stack_t && other) noexcept:
      data_(std::move(other.data_))
    {}
    stack_t & operator=(stack_t && other)
    {
      if (std::addressof(other) != this)
      {
        std::swap(data_, other.data_);
      }
      return *this;
    }
    void push(const T & value)
    {
      data_.push_front(value);
    }
    void pop()
    {
      data_.pop_front();
    }
    T & top() const noexcept
    {
      return data_.front();
    }
    size_t size() const noexcept
    {
      return data_.size();
    }
    bool empty() const noexcept
    {
      return data_.empty();
    }
    ~Stack() = default;
  private:
    std::list< T > data_;
  };
}

#endif