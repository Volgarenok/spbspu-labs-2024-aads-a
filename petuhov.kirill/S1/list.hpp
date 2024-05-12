#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"

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

    Iterator< T > begin() noexcept;
    Iterator< T > end() noexcept;

    ~List();

    private:
      Node* head_;
      Node* tail_;
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
    Node< T > *new_node = new Node< T >(value);
    head_ = new Node< T >(value, head_);
    if (tail_ == nullptr)
    {
      tail_ = new_node;
    }
  }

  template < typename T >
  void List< T >::pop_front()
  {
    Node< T > *temp = head_;
    head_ = head_->next_;
    if (head_ == nullptr)
    {
      tail_ = nullptr;
    }
    delete temp;
  }

  template < typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_front();
    }
    tail_ = nullptr;
  }

  template < typename T >
  void List< T >::swap(List &other)
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T >
  Iterator< T > List< T >::begin() noexcept
  {
    return Iterator< T >(head_);
  }

  template < typename T >
  Iterator< T > List< T >::end() noexcept
  {
    return Iterator< T >(tail_->next);
  }

}

#endif
