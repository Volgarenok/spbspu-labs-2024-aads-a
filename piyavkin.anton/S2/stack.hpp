#ifndef STACK_HPP
#define STACK_HPP
#include <list.hpp>

namespace piyavkin
{
  template< class T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack< T >&) = default;
    Stack(Stack&& stack):
      list(std::move(stack.list))
    {}
    ~Stack() = default;
    Stack< T >& operator=(const Stack&) = default;
    Stack< T >& operator=(Stack&& stack)
    {
      if (this != std::addressof(stack))
      {
        list = std::move(stack.list);
      }
      return *this;
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
