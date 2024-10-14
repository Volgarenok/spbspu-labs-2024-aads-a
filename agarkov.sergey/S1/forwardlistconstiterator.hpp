#ifndef FORWARDLISTCONSTITERATOR_HPP
#define FORWARDLISTCONSTITERATOR_HPP

#include <list.hpp>

namespace agarkov
{
  class ForwardListConstIterator
  {
  friend class ForwardList< T >;
  public:
    ForwardListConstIterator();
    ~ForwardListConstIterator() = default;
    explicit ForwardListConstIterator(const details::List< T >* rhs);
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


}


#endif
