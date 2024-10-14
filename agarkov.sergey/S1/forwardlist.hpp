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
    bool empty() const;
    void clear();
    void push_front(const T& value);
    void push_front(T&& value);


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


  template< typename T >
  bool ForwardList< T >::empty() const
  {
    return head_ == nullptr;
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

  template< typename T >
  void ForwardList< T >::push_front(const T& value)
  {
    details::List< T >* temp = new details::List< T >();
    temp->data_ = value;
    temp->next_ = head_;
    head_ = temp;
  }

  template< typename T >
  void ForwardList< T >::push_front(T&& value)
  {
    push_front(value);
  }



}

#endif
