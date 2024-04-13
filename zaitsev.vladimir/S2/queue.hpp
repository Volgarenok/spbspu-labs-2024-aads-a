#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "deque.hpp"
#include <deque>
namespace zaitsev
{
  template< typename T, typename Container = Deque< T > >
  class Queue
  {
  public:
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;

    T& front()
    {
      return container.front();
    }
    bool empty() const
    {
      return container.empty();
    }
    size_t size() const
    {
      return container.size();
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
    iterator begin()
    {
      return container.begin();
    }
    iterator end()
    {
      return container.end();
    }
    const_iterator begin() const
    {
      return container.cbegin();
    }
    const_iterator end() const
    {
      return container.cend();
    }
    const_iterator cbegin() const
    {
      return container.cbegin();
    }
    const_iterator cend() const
    {
      return container.cend();
    }
  protected:
    Container container;
  };
}
#endif
