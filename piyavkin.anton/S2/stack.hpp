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
    T drop()
    {
      T temp = list.back();
      list.pop_back();
      return temp;
    }
    bool empty() const
    {
      return list.empty();
    }
  private:
    List< T > list;
  };
}
#endif