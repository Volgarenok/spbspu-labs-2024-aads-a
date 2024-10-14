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
  private:
    details::List< T >* ptr_;
  };

}
#endif
