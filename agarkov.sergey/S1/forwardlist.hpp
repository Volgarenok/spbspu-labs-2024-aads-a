#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include "list.hpp"

namespace agarkov
{
  template< typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ~ForwardList();
    ForwardList(const ForwardList< T >& other);
    ForwardList(ForwardList< T >&& other);
    ForwardList< T >& operator=(const ForwardList< T >& other);
    ForwardList< T >& operator=(ForwardList< T >&& other);

  private:
    details::List< T >* head_;
  };


  template< typename T >
  ForwardList< T >::ForwardList():
    head_(nullptr)
  {
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    ::operator delete(head_);
  }

  // ForwardList(const ForwardList< T >& other);
  // ForwardList(ForwardList< T >&& other);
  // ForwardList< T >& operator=(const ForwardList< T >& other);
  // ForwardList< T >& operator=(ForwardList< T >&& other);
}

#endif
