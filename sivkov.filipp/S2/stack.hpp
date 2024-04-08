#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

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
    Stack< T >& operator=(const Stack< T >&);
    Stack< T >& operator=(Stack< T >&& other) noexcept;

  private:
    List<T> list;
  };

  template<typename T>
  void Stack<T>::push(const T& value)
  {
    list.push_front(value);
  }

  template<typename T>
  void Stack<T>::pop()
  {
    if (!list.empty())
    {
      list.pop_front();
    }
  }

  template<typename T>
  T& Stack<T>::top()
  {
    if (!list.empty())
    {
      return list.front();
    }
    throw std::out_of_range("Stack is empty");
  }

  template<typename T>
  bool Stack<T>::empty() const
  {
    return list.empty();
  }

  template<typename T>
  size_t Stack<T>::size() const
  {
    return list.getSize();
  }
}
#endif
