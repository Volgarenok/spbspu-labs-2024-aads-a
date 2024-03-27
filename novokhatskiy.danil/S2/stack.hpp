#ifndef STACK_HPP
#define STACK_HPP

#include "forward_list.hpp"

namespace novokhatskiy
{
  template < class T > class Stack
  {
  public:
    Stack() = default;
    T& top() const;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void push(const T& value);
    void pop();
    ~Stack() = default;

  private:
    ForwardList< T > data_;
  };

  template < class T > T& Stack< T >::top() const
  {
    return data_.front();
  }

  template < class T > bool Stack< T >::empty() const noexcept
  {
    return data_.empty();
  }

  template < class T > size_t Stack< T >::size() const noexcept
  {
    return data_.max_size();
  }

  template < class T > void Stack< T >::push(const T& value)
  {
    data_.push_front(value);
  }

  template < class T > void Stack< T >::pop()
  {
    data_.pop_front();
  }
}

#endif
