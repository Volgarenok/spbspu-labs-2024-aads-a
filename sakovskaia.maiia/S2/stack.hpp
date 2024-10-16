#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"

namespace sakovskaia
{
  template< typename T >
  class Stack
  {
  public:
    void push_back(const T & value);
    void push(T && value);
    T & back();
    const T & back() const;
    void pop_back();
    T & front() noexcept;
    const T & front() const noexcept;
    T pop();
    T & top();
    const T & top() const;
    bool empty() const noexcept;
    Stack() = default;
    Stack(const Stack & other) = default;
    Stack(Stack && other) noexcept = default;
    Stack & operator=(const Stack & other) = default;
    Stack & operator=(Stack && other) noexcept = default;
  private:
    List< T > data;
  };

  template< typename T >
  void Stack< T >::push_back(const T & value)
  {
    data.push_back(value);
  }

  template< typename T >
  void Stack< T >::push(T && value)
  {
    data.push_back(std::move(value));
  }

  template< typename T >
  T & Stack< T >::back()
  {
    return data.back();
  }

  template< typename T >
  const T & Stack< T >::back() const
  {
    return data.back();
  }

  template< typename T >
  void Stack< T >::pop_back()
  {
    data.pop_back();
  }

  template< typename T >
  T & Stack< T >::front() noexcept
  {
    return data.front();
  }

  template< typename T >
  const T & Stack< T >::front() const noexcept
  {
    return data.front();
  }

  template< typename T >
  T Stack< T >::pop()
  {
    if (data.empty())
    {
      throw std::runtime_error("Stack is empty");
    }
    T value = std::move(data.back());
    data.pop_back();
    return value;
  }

  template< typename T >
  T & Stack< T >::top()
  {
    if (empty()) throw std::runtime_error("Stack is empty");
    return data.back();
  }

  template< typename T >
  const T & Stack< T >::top() const
  {
    if (empty()) throw std::runtime_error("Stack is empty");
    return data.back();
  }

  template< typename T >
  bool Stack< T >::empty() const noexcept
  {
    return data.empty();
  }
}

#endif
