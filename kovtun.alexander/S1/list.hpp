#ifndef LIST_HPP
#define LIST_HPP

#include "const_iterator.hpp"

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
    Node< T > * temp = new Node< T >(node);
    temp->next = head_;
    if (head_ == nullptr)
    {
      head_ = temp;
      tail_ = temp;
      return;
    }

    head_->prev = temp;
    head_ = temp;

    size_++;
  }

  template< typename T >
  void List< T >::push_back(const T & node)
  {
    Node< T > * temp = new Node< T >(node);
    temp->prev = tail_;
    if (tail_ == nullptr)
    {
      head_ = temp;
      tail_ = temp;
      return;
    }

    tail_->next = temp;
    tail_ = temp;

    size_++;
  }

  template< typename T >
  void List< T >::pop_front()
  {
    if (head_ == nullptr)
    {
      return;
    }

    Node< T > * temp = head_->next;
    if (temp == nullptr)
    {
      tail_ = nullptr;
    }

    temp->prev = nullptr;
    delete head_;
    head_ = temp;

    size_--;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    if (tail_ == nullptr)
    {
      return;
    }

    Node< T > * temp = tail_->prev;
    if (temp == nullptr)
    {
      head_ = nullptr;
    }

    temp->next = nullptr;
    delete tail_;
    tail_ = temp;

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
