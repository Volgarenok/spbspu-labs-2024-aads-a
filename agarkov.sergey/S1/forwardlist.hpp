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
    void clear();

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

  template< typename T >
  void ForwardList< T >::clear()
  {
    if (!head_)
    {
      return;
    }

    while(head_->next_ != nullptr)
    {
      details::List< T >* temp = head_->next_;
      delete head_;
      head_ = temp;
    }
    delete head_;
    head_ = nullptr;
  }

  // ForwardList(const ForwardList< T >& other);
  // ForwardList(ForwardList< T >&& other);
  // ForwardList< T >& operator=(const ForwardList< T >& other);
  // ForwardList< T >& operator=(ForwardList< T >&& other);
}

#endif
