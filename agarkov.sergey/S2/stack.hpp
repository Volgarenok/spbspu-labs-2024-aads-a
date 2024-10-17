#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include <list.hpp>

namespace agarkov
{
  template< typename T >
  class Stack
  {
    public:
      Stack();
      ~Stack();
      Stack(const Stack< T >& other);
      Stack< T >& operator=(const Stack< T >& other);
      void push(const T& value);
      void pop();
      T get() const;
      bool isEmpty() const;
      void clear();
    private:
      details::List< T >* top_;
  };

  template< typename T >
  Stack< T >::Stack():
    top_(nullptr)
  {}

  template< typename T >
  bool Stack< T >::isEmpty() const
  {
    return (top_ == nullptr);
  }

  template< typename T >
  void Stack< T >::push(const T& value)
  {
    details::List< T >* temp = new details::List< T >{value, top_};
    top_ = temp;
  }

  template< typename T >
  T Stack< T >::get() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    return top_->data_;
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    details::List< T >* temp = top_->next_;
    delete top_;
    top_ = temp;
  }

  template< typename T >
  Stack< T >::~Stack()
  {
    clear();
  }

  template< typename T >
  Stack< T >::Stack(const Stack< T >& other):
    top_(nullptr)
  {
    try
    {
      details::List< T >* other_value = other.top_;
      while (other_value != nullptr)
      {
        push(other_value->data_);
        other_value = other_value->next_;
      }
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack< T >& other)
  {
    if (this != std::addressof(other))
    {
      Stack< T > temp(other);
      std::swap(top_, other.top_);
    }
    return *this;
  }



  template < typename T >
  void Stack< T >::clear()
  {
    while (!isEmpty())
    {
      pop();
    }
  }
}

#endif
