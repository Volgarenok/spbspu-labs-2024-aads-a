#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <bdlist.hpp>

namespace ishmuratov
{
  template< class T, class Container = List< T > >
  class Queue
  {
    public:
      Queue():
        c_(Container())
      {}

      ~Queue() = default;

      void push(const T & rhs)
      {
        c_.pushFront(rhs);
      }

      T drop()
      {
        T value = c_.back();
        c_.popBack();
        return value;
      }

      T & front()
      {
        return c_.front();
      }

      T & back()
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
      Container c_;
  };
}

#endif
