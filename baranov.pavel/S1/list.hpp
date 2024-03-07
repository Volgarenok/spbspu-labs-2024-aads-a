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
      T & operator[](size_t);
      Iterator< T > begin();
      Iterator< T > end();
      bool empty() const;
      void push_back(T data);
      void pop_back();
      void push_front(T data);
      void pop_front();
      void clear();
      void swap(List &);
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
  T & List< T >::operator[](size_t index)
  {
  assert(!empty());
  {
    Iterator< T > iterator = begin();
    return *(iterator[index]);
  }

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
  void List< T >::push_back(T data)
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
  void List< T >::pop_back()
  {
    assert(!empty());
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
  template< class T >
  void List< T >::push_front(T data)
  {
    Node< T > * topush = new Node< T >{ data };
    if (empty())
    {
      head_ = topush;
      tail_ = topush;
    }
    else
    {
      head_->prev_ = topush;
      head_ = topush;
    }
  }

  template< class T >
  void List< T >::pop_front()
  {
    assert(!empty());
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      Node< T > newhead = head_->next_;
      delete head_;
      head_ = newhead;
      head_->prev = nullptr;
    }
  }

  template< class T >
  void List< T >::clear()
  {
    while(head_)
    {
      pop_front();
    }
  }

  template< class T >
  void List< T >::swap(List & rhs)
  {
    std::swap(rhs.head_, head_);
    std::swap(rhs.tail_, tail_);
  }
}

#endif

