#ifndef STACK_HPP
#define STACK_HPP

#include <utility>
#include "dataArray.hpp"

namespace isaychev
{
  template < class T, class Container = DataArray< T > >
  class Stack
  {
   public:
    Stack() = default;
    Stack(const Container & rhs);
    Stack(Container && rhs);

    void push(const T & rhs);
    void pop();
    T & top();
    const T & top() const;

    template < class... Args >
    void emplace(Args&&... args);

    bool empty() const;
    size_t size() const;
    void swap(Stack & rhs);

   private:
    Container con_;
  };

  template < class T, class Container >
  Stack< T, Container >::Stack(const Container & rhs):
   con_(rhs)
  {}

  template < class T, class Container >
  Stack< T, Container >::Stack(Container && rhs):
   con_(rhs)
  {}

  template < class T, class Container >
  void Stack< T, Container >::push(const T & rhs)
  {
    con_.push_back(rhs);
  }

  template < class T, class Container >
  void Stack< T, Container >::pop()
  {
    con_.pop_back();
  }

  template < class T, class Container >
  T & Stack< T, Container >::top()
  {
    return con_.back();
  }

  template < class T, class Container >
  const T & Stack< T, Container >::top() const
  {
    return con_.back();
  }

  template < class T, class Container >
  template < class... Args >
  void Stack< T, Container >::emplace(Args&&... args)
  {
    con_.emplace_back(std::forward< Args... >(args...));
  }

  template < class T, class Container >
  bool Stack< T, Container >::empty() const
  {
    return con_.empty();
  }

  template < class T, class Container >
  size_t Stack< T, Container >::size() const
  {
    return con_.size();
  }

  template < class T, class Container >
  void Stack< T, Container >::swap(Stack & rhs)
  {
    con_.swap(rhs.con_);
  }
}

#endif
