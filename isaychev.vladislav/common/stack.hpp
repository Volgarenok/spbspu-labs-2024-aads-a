#ifndef STACK_HPP
#define STACK_HPP

#include <list/list.hpp>

namespace isaychev
{
  template < class T >
  class Stack
  {
   public:
    Stack() = default;

    void push(const T & rhs);
    void pop();
    T & top() noexcept;
    const T & top() const noexcept;

    bool empty() const noexcept;
    void swap(Stack & rhs) noexcept;

   private:
     List< T > con_;
  };

  template < class T >
  void Stack< T >::push(const T & rhs)
  {
    con_.push_front(rhs);
  }

  template < class T >
  void Stack< T >::pop()
  {
    con_.pop_front();
  }

  template < class T >
  T & Stack< T >::top() noexcept
  {
    return con_.front();
  }

  template < class T >
  const T & Stack< T >::top() const noexcept
  {
    return con_.front();
  }

  template < class T >
  bool Stack< T >::empty() const noexcept
  {
    return con_.empty();
  }

  template < class T >
  void Stack< T >::swap(Stack & rhs) noexcept
  {
    con_.swap(rhs.con_);
  }
}

#endif
