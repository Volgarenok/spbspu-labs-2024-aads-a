#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list.hpp>

namespace piyavkin
{
  template< class T >
  class Queue
  {
  public:
    bool operator==(const Queue& queue) const
    {
      return queue.list == list;
    }
    bool operator!=(const Queue& queue) const
    {
      return *this != queue;
    }
    void push(const T& value)
    {
      list.push_back(value);
    }
    T& back()
    {
      return list.back();
    }
    T& front()
    {
      return list.front();
    }
    const T& back() const
    {
      return list.back();
    }
    const T& front() const
    {
      return list.front();
    }
    void pop()
    {
      list.pop_front();
    }
    bool empty() const noexcept
    {
      return list.empty();
    }
    size_t size() const noexcept
    {
      return list.size();
    }
    void swap(Queue< T >& queue) noexcept
    {
      list.swap(queue.list);
    }
    template< class... Args >
    void emplace(Args&&... args)
    {
      list.emplace(std::forward< Args >(args)...);
    }
  private:
    List< T > list;
  };
}
#endif
