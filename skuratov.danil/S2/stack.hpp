#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace skuratov
{
  template< typename T >
  class Stack
  {
  public:
    void push(T& diff);
    T drop();
    bool empty();
    size_t size();
    T& top();
  private:
    List< T > stack_;
  };
}

#endif
