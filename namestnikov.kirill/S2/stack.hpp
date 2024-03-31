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
      std::cout << "IM HERE";
      if (std::addressof(other) != this)
      {
        std::swap(data_, other.data_);
      }
      return *this;
    }
    ~Stack() = default;
  private:
    std::list< T > data_;
  };
}

#endif