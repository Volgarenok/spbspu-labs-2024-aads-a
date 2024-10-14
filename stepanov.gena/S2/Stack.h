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
