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
    void swap(T & other) noexcept;
  private:
    Container container_;
  };

  template< class T, class Container >
  void swap(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs) noexcept;

  template< class T, class Container >
  bool operator==(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs);

  template< class T, class Container >
  bool operator<(const Stack<T, Container> & lhs, const Stack<T, Container> & rhs);
}

#endif
