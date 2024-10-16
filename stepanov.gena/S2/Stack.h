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

template < typename T >
void stepanov::Stack<T>::pushTop(const T& newHead)
{
  dataBase_.push_front(newHead);
}

template < typename T >
void stepanov::Stack< T >::popTop()
{
  if (!isEmpty())
  {
    dataBase_.pop_front();
  }
}

template < typename T >
bool stepanov::Stack< T >::isEmpty() const noexcept
{
  return dataBase_.empty();
}

template < typename T >
size_t& stepanov::Stack< T >::getSize() const noexcept
{
  return dataBase_.size();
}

template < typename T >
const T& stepanov::Stack< T >::getHead() const
{
  return dataBase_.front();
}

#endif
