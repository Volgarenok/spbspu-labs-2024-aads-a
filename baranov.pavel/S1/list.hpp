#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"

namespace baranov
{
  template< class T >
  class List
  {
    public:
      List();
      Iterator< T > begin();
      Iterator< T > end();
    private:
      Node< T > * head_;
      Node< T > * tail_;
  };


  template< class T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}

  template< class T >
  Iterator< T > List< T >::begin()
  {
    return Iterator< T >(head_);
  }

  template< class T >
  Iterator< T > List< T >::end()
  {
    return Iterator< T >(nullptr);
  }

}

#endif

