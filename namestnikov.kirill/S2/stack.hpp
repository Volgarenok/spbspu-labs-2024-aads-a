#ifndef STACK_HPP
#define STACK_HPP

#include <list>
#include <cstddef>

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
