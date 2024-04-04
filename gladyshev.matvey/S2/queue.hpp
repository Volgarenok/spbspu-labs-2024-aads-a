#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list>

namespace gladyshev
{
  template < class T, class Container = std::list< T >>
  class Queue
  {
  public:
    Queue():
      list_(Container())
    {}
    T& front()
    {
      return list_.back();
    }
    T& back()
    {
      return list_.back();
    }
    bool empty() const
    {
      return list_.empty();
    }
    size_t size()
    {
      return list_.size();
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
    void reverse()
    {
      list_.reverse();
    }
  private:
    Container list_;
  };
}

#endif
