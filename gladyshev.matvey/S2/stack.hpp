#ifndef STACK_HPP
#define STACK_HPP

#include "../common/list.hpp"

namespace gladyshev
{
  template < class T, class Container = List< T > >
  class Stack
  {
  public:
    Stack():
      list_(Container())
    {}
    Stack(const Stack& other):
      list_(other.list_)
    {}
    Stack(Stack&& other):
      list_(std::move(other.list_))
    {}
    T& top()
    {
      return list_.front();
    }
    bool empty()
    {
      return list_.empty();
    }
    size_t size()
    {
      return list_.size();
    }
    T drop()
    {
      T temp = list_.front();
      list_.pop_front();
      return temp;
    }
    void push(const T& other)
    {
      list_.push_front(other);
    }
  private:
    Container list_;
  };
}

#endif
