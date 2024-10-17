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
    private:
      details::List< T >* top_;
  };

  template< typename T >
  Stack< T >::Stack():
    top_(nullptr)
  {}

}

#endif
