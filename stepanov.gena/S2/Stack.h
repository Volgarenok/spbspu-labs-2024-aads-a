#ifndef STACK_H
#define STACK_H

#include <list.hpp>

namespace stepanov
{
  template < typename T >
  class Stack
  {
  public:
    Stack() = default;
    ~Stack() = default;
    Stack(const Stack & stack) = default;
    Stack(Stack && stack) = default;
    Stack & operator=(const Stack & stack) = default;
    Stack & operator=(Stack && rhStack) = default;

    void pushTop(const T& newHead);
    void popTop();
    bool isEmpty() const noexcept;
    size_t& getSize() const noexcept;
    const T& getHead() const;
  private:
    List< T > dataBase_;
  };
}

#endif
