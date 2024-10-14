#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

namespace agarkov
{
  template< typename T >
  class ForwardList
  {
  public:
    ForwardList();
  private:
    details::List< T >* head_;
  };
}

#endif
