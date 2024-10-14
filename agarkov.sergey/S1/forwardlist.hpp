#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

namespace agarkov
{
  template< typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ~ForwardList();
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

}

#endif
