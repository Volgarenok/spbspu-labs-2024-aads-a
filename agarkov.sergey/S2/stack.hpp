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


      T get() const;


    private:
      details::List< T >* top_;
  };

  template< typename T >
  Stack< T >::Stack():
    top_(nullptr)
  {}




  template< typename T >
  T Stack< T >::get() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    return top_->data_;
  }







}

#endif
