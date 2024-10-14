#ifndef FORWARDLISTCONSTITERATOR_HPP
#define FORWARDLISTCONSTITERATOR_HPP

#include "list.hpp"
#include <memory>

namespace agarkov
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ForwardListConstIterator
  {
  friend class ForwardList< T >;
  public:
    ForwardListConstIterator();
    ~ForwardListConstIterator() = default;
    explicit ForwardListConstIterator(const details::List< T >* rhs);
    ForwardListConstIterator< T >& operator++();
    ForwardListConstIterator< T > operator++(int);

  private:
    const details::List< T >* ptr_;
  };

  template< typename T >
  ForwardListConstIterator< T >::ForwardListConstIterator():
    ptr_(nullptr)
  {
  }

  template< typename T >
  ForwardListConstIterator< T >::ForwardListConstIterator(const details::List< T >* rhs):
    ptr_(rhs)
  {
  }

  template< typename T >
  ForwardListConstIterator< T >& ForwardListConstIterator< T >::operator++()
  {
    if (ptr_)
    {
      ptr_ = ptr_->next_;
    }
    return *this;
  }

  template< typename T >
  ForwardListConstIterator< T > ForwardListConstIterator< T >::operator++(int)
  {
    ForwardListConstIterator< T > temp(*this);
    if (ptr_)
    {
      ptr_ = ptr_->next_;
    }
    return temp;
  }


}


#endif
