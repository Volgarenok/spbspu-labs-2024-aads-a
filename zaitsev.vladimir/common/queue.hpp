#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "deque.hpp"

namespace zaitsev
{
  template< typename T, typename Container = PseudoDeque< T > >
  class Queue
  {
  public:
    T& front()
    {
      return container.front();
    }
    const T& front() const
    {
      return container.front();
    }
    T& back()
    {
      return container.back();
    }
    const T& back() const
    {
      return container.back();
    }
    bool empty() const
    {
      return container.empty();
    }
    size_t size() const
    {
      return container.size();
    }
    template< class... Args >
    void emplace(Args&&... args)
    {
      container.emplace_back(std::forward< Args >(args)...);
    }
    void push(const T& value)
    {
      container.push_back(value);
    }
    void push(T&& value)
    {
      container.push_back(std::move(value));
    }
    void pop()
    {
      container.pop_front();
    }
    void clear()
    {
      container.clear();
    }
  protected:
    Container container;
  };
}
#endif
