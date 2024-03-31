#ifndef STACK_HPP
#define STACK_HPP

#include <list>

namespace namestnikov
{
  template< class T >
  class Stack
  {
  public:
    Stack() = default;
    ~stack() = default;
  private:
    std::list data_;
  };
}

#endif