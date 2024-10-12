#ifndef LIST_HPP
#define LIST_HPP

#include "const_iterator.hpp"
#include <cassert>

namespace kovtun
{
  template< typename T >
  class List
  {
  public:
    List();
    ~List() = default;

    ConstIterator< T > cbegin() const;
    ConstIterator< T > cend() const;

    bool empty();

    void push_front(const T &);
    void push_back(const T &);
    void pop_front();
    void pop_back();
    void clear();
    void swap();

  private:
    Node< T > * head_;
    Node< T > * tail_;

    size_t size_;
  };

  template< typename T >
  List< T >::List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
  {}

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const
  {
    return ConstIterator< T >(tail_);
  }

  template< typename T >
  void List< T >::push_front(const T & node)
  {
    size_++;
  }

  template< typename T >
  void List< T >::push_back(const T & node)
  {
    if (head_ == nullptr)
    {
      head_ = new Node< T >(node);
      tail_ = new Node< T >();
      head_->next = tail_;
      tail_->prev = head_;
    }
    else
    {
      Node< T > * temp = new Node< T >(node);
      temp->next = tail_;
      temp->prev = tail_->prev;
      tail_->prev->next = temp;
      tail_->prev = temp;
    }

    size_++;
  }

  template< typename T >
  void List< T >::pop_front()
  {
    size_--;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    if (tail_ == nullptr)
    {
      return;
    }

    if (tail_->prev == head_)
    {
      delete head_;
      delete tail_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      Node< T > * last = tail_->prev;
      last->prev->next = tail_;
      tail_->prev = last->prev;

      delete last;
    }

    size_--;
  }

  template< typename T >
  bool List< T >::empty()
  {
    return size_ == 0;
  }

  template< typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_back();
    }
  }
}

#endif
