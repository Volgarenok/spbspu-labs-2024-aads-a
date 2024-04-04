#ifndef STACK_HPP
#define STACK_HPP

#include <list>
#include <cstddef>

namespace
{
  template< class T, class Container = std::list< T > >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack & stack);
    Stack(Stack && stack);
    template< class InputIt >
    Stack(InputIt first, InputIt last);
    explicit Stack(const Container & cont);
    explicit Stack(Container && cont);
    ~Stack();
    Stack & operator=(const Stack & other);
    Stack & operator=(Stack && other);
    bool empty();
    size_t size();
    void push(const T & value);
    void push(T && value);
    template< class... Args >
    void emplace(Args&&... args);
    void pop();
    void swap(Stack & other) noexcept;
  private:
    Container container_;
  };

  template< class T, class Container >
  Stack< T, Container >::Stack(const Stack & stack):
    container_(stack.container_)
  {}

  template< class T, class Container >
  Stack< T, Container >::Stack(Stack && stack):
    container_(stack.container_)
  {}

  template< class T, class Container >
  template< class InputIt >
  Stack< T, Container >::Stack(InputIt first, InputIt last):
    container_(Container(first, last))
  {}

  template< class T, class Container >
  Stack< T, Container >::Stack(const Container & cont):
    container_(cont)
  {}

  template< class T, class Container >
  Stack< T, Container >::Stack(Container && cont):
    container_(std::move(cont))
  {}

  template< class T, class Container >
  Stack< T, Container >::~Stack() = default;

  template< class T, class Container >
  Stack< T, Container > & Stack< T, Container >::operator=(const Stack & other)
  {
    if (*this != &other)
    {
      Stack< T, Container > temp(other);
      swap(temp);
    }
    return *this;
  }

  template< class T, class Container >
  Stack< T, Container > & Stack< T, Container >::operator=(Stack && other)
  {
    if (*this != &other)
    {
      Stack< T, Container > temp(std::move(other));
      swap(temp);
    }
    return *this;
  }

  template< class T, class Container >
  void Stack<T, Container>::swap(Stack<T, Container> & rhs) noexcept
  {
    container_.swap(rhs);
  }

  template< class T, class Container >
  void swap(Stack<T, Container> & lhs, Stack<T, Container> & rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template< class T, class Container >
  bool operator==(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs);

  template< class T, class Container >
  bool operator<(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs);
}

#endif
