#ifndef STACK_HPP
#define STACK_HPP
#include <stdexcept>
#include "forward_list.hpp"

namespace spiridonov
{
  template <typename T>
  class Stack
  {
  private:
    List<T> list;

  public:
    void push(const T& value)
    {
      list.push_back(value);
    }

    T pop()
    {
      if (empty())
      {
        throw std::out_of_range("Stack is empty");
      }

      T value = list.pop_back();
      return value;
    }

    bool empty() const
    {
      return list.is_empty();
    }
  };
}

#endif
