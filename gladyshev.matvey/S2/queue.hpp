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
    Queue(const Queue& other):
      list_(other.list_)
    {}
    Queue(Queue&& other):
      list_(std::move(other.list_))
    {}
    T& front()
    {
      return list_.front();
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
