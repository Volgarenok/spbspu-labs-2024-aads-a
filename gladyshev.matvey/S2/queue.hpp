#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "array.hpp"

namespace gladyshev
{
  template < class T, class Container = DynArray< T > >
  class Queue
  {
  public:
    Queue():
      list_(Container())
    {}
    Queue(const Queue& other):
      list_(other.list_)
    {}
    Queue(Queue&& other) noexcept:
      list_(std::move(other.list_))
    {}
    bool empty() const noexcept
    {
      return list_.empty();
    }
    T drop()
    {
      T temp = list_.back();
      list_.pop_back();
      return temp;
    }
    void push(const T& other)
    {
      list_.push_front(other);
    }
    void reverse() noexcept
    {
      list_.reverse();
    }
  private:
    Container list_;
  };
}

#endif
