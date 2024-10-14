#ifndef FORWARDLISTITERATOR
#define FORWARDLISTITERATOR

#include <list.hpp>

namespace agarkov
{
  template< typename T >
  class ForwardListIterator
  {
  public:
    ForwardListIterator();
    ~ForwardListIterator() = default;
    explicit ForwardListIterator(details::List< T >* rhs);
  private:
    details::List< T >* ptr_;
  };

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator():
    ptr_(nullptr)
  {
  }
  
  template< typename T >
  ForwardListIterator< T >::ForwardListIterator(details::List< T >* rhs):
    ptr_(rhs)
  {
  }



}
#endif
