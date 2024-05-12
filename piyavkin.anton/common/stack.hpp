#ifndef STACK_HPP
#define STACK_HPP
#include <list.hpp>

namespace piyavkin
{
  template< class T >
  class Stack
  {
  public:
    bool operator==(const Stack& stack) const
    {
      return stack.list == list;
    }
    bool operator!=(const Stack& stack) const
    {
      return *this != stack;
    }
    void push(const T& value)
    {
      list.push_back(value);
    }
    T& top()
    {
      return list.back();
    }
    const T& top() const
    {
      return list.back();
    }
    void pop()
    {
      list.pop_back();
    }
    bool empty() const noexcept
    {
      return list.empty();
    }
    size_t size() const noexcept
    {
      return list.size();
    }
    void swap(Stack< T >& stack) noexcept
    {
      list.swap(stack.list);
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
