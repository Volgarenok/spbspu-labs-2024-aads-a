#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"

namespace petuhov
{
  template < typename T >
  class List
  {
    List();
    T &front();
    const T &front() const;
    bool empty() const;
    void push_front(const T &value);
    void pop_front();
    void clear();
    void swap(List &other);
    ~List();

    private:
      Node* head_;
  };

  template < typename T >
  List< T >::List():
    head_(nullptr)
  {}

  template < typename T >
  T &List< T >::front()
  {
    return head_->value_;
  }

  template < typename T >
  const T &List< T >::front() const
  {
    return head_->value_;
  }

  template < typename T >
  bool List< T >::empty() const
  {
    return head_ == nullptr;
  }

  template < typename T >
  void List< T >::push_front(const T &value)
  {
    head_ = new Node< T >(value, head_);
  }

  template < typename T >
  void List< T >::pop_front()
  {
    Node< T > *temp = head_;
    head_ = head_->next_;
    delete temp;
  }

  template < typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template < typename T >
  void List< T >::swap(List &other)
  {
    std::swap(head_, other.head_);
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
  }

}

#endif
