#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list.hpp>

namespace piyavkin
{
  template< class T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue< T >&) = default;
    Queue(Queue&& queue):
      list(std::move(queue.list))
    {}
    ~Queue() = default;
    Queue< T >& operator=(const Queue&) = default;
    Queue< T >& operator=(Queue&& queue)
    {
      if (this != std::addressof(queue))
      {
        list = std::move(queue.list);
      }
      return *this;
    }
    void push(const T& value)
    {
      list.push_back(value);
    }
    T back()
    {
      return list.back();
    }
    T front()
    {
      return list.front();
    }
    T drop()
    {
      T temp = list.front();
      list.pop_front();
      return temp;
    }
    bool empty() const
    {
      return list.empty();
    }
    size_t size() const
    {
      return list.size();
    }
  private:
    List< T > list;
  };
}
#endif