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
      bool empty() const;
      void push(T data);
      void pop();
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

  template< class T >
  bool List< T >::empty() const
  {
    return head_ == nullptr || tail_ == nullptr;
  }

  template< class T >
  void List< T >::push(T data)
  {
    Node< T > * topush = new Node< T >{ data };
    if (empty())
    {
      head_ = topush;
      tail_ = topush;
    }
    else
    {
      tail_->next_ = topush;
      tail_ = topush;
    }
  }

  template< class T >
  void List< T >::pop()
  {
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      Node< T > newtail = tail_->prev_;
      delete tail_;
      tail_ = newtail;
      tail_->next = nullptr;
    }
  }
}

#endif

