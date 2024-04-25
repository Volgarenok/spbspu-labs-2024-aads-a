#ifndef STACK_HPP
#define STACK_HPP

#include <bdlist.hpp>

namespace ishmuratov
{
  template< class T >
  class Stack
  {
    public:
      void push(const T & rhs)
      {
        c_.pushBack(rhs);
      }

      T drop()
      {
        T value = c_.back();
        c_.popBack();
        return value;
      }

      T & top()
      {
        return c_.back();
      }

      bool empty() const
      {
        return c_.empty();
      }

      size_t size()
      {
        return c_.size();
      }

    private:
      List< T > c_;
  };
}

#endif
