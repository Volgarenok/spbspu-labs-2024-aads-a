#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"

namespace baranov
{
  template< class T >
  class List
  {
    public:
      List();
    private:
      Node< T > * head_;
      Node< T > * tail_;
  };


  template < class T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}
}

#endif

