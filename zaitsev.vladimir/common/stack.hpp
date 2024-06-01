#ifndef STACK_HPP
#define STACK_HPP
#include "deque.hpp"

namespace zaitsev
{
  template< typename T, typename Container = PseudoDeque< T > >
  class Stack
  {
  public:
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
    template< class... Args >
    void emplace(Args&&... args)
    {
      container.emplace_front(std::forward< Args >(args)...);
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
