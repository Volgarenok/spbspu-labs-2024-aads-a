#ifndef STACK_HPP
#define STACK_HPP
#include "deque.hpp"
namespace zaitsev
{
  template< typename T, typename Container = Deque< T > >
  class Stack
  {
  public:
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;

    T& top()
    {
      return container.front();
    }
    const T& top() const
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
      container.push_front(value);
    }
    void push(T&& value)
    {
      container.push_front(std::move(value));
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
