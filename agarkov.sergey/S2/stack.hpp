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
  T Stack< T >::get() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    return top_->data_;
  }


  template< typename T >
  Stack< T >::~Stack()
  {
    clear();
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
