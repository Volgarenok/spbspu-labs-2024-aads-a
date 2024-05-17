#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace skuratov
{
  template< typename T >
  class Stack
  {
  public:
    void push(T& diff)
    {
      stack_.pushBack(diff);
    }
    void drop()
    {
      stack_.popBack(diff);
    }
    bool empty() noexcept
    {
      return stack_.empty();
    }
    size_t size() noexcept
    {
      return stack_.size();
    }
    T& top() noexcept
    {
      return stack_.back();
    }
  private:
    List< T > stack_;
  };
}

#endif
