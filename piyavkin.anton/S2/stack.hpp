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
    T drop()
    {
      T temp = list.back();
      list.pop_back();
      return temp;
    }
    bool empty() const noexcept
    {
      return list.empty();
    }
    size_t size() const noexcept
    {
      return list.size();
    }
  private:
    List< T > list;
  };
}
#endif
