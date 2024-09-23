#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace skuratov
{
  template< typename T >
  class Stack
  {
  public:
    void push(const T& diff)
    {
      stack_.pushBack(diff);
    }
    void drop()
    {
      stack_.popBack();
    }
    bool empty() const noexcept
    {
      return stack_.empty();
    }
    size_t size() const noexcept
    {
      return stack_.getSize();
    }
    T& top() noexcept
    {
      return stack_.back();
    }
    const T& top() const noexcept
    {
      return stack_.back();
    }
  private:
    List< T > stack_;
  };
}

#endif
