#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "array.hpp"

namespace gladyshev
{
  template < class T, class Container = DynArray< T > >
  class Queue
  {
  public:
    bool empty() const noexcept
    {
      return array_.empty();
    }
    T drop()
    {
      T temp = array_.back();
      array_.pop_back();
      return temp;
    }
    void push(const T& other)
    {
      array_.push_front(other);
    }
    void reverse() noexcept
    {
      array_.reverse();
    }
  private:
    Container array_;
  };
}

#endif
