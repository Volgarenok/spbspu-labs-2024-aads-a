#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace sivkov
{
  template<typename T>
  class Stack
  {
  public:
    Stack()
    {}

    Stack(const Stack& other):
      list(other.list)
    {}

    Stack(Stack&& other) noexcept:
      list(std::move(other.list))
    {}

    void push(const T& value);
    void pop();
    T& top();
    bool empty() const;
    size_t size() const;

  private:
    List<T> list;
  };
}
#endif
