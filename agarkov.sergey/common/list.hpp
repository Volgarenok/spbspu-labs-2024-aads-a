#ifndef LIST_HPP
#define LIST_HPP

namespace details
{
  template < typename T >
  struct List
  {
    T data_;
    List< T >* next_;
  };
}

#endif
