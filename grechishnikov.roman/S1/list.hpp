#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <algorithm>
#include <cstddef>
#include "node.hpp"
#include "iterator.hpp"

namespace grechishnikov
{
  template< typename T >
  class List
  {
  public:
    List();
    List(const List< T >&);
    List(List< T >&& other);
    ~List();

    List< T >& operator=(const List< T >&);
    List< T >& operator=(List< T >&&);
    T& operator[](size_t);

    bool empty();

    void clear();
    void push_back(const T&);
    void push_front(const T&);
    void pop_back();
    void pop_front();

  private:
    Node< T >* head_;
    Node< T >* tail_;
  };

  template< typename T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}

  template< typename T >
  List< T >::List(const List< T >& other):
    head_(nullptr),
    tail_(nullptr)
  {
    Node< T >* node = other.head_;
    while(node)
    {
      push_back(node->data_);
      node = node->next_;
    }
  }

  template< typename T >
  List< T >::List(List< T >&& other):
    head_(nullptr),
    tail_(nullptr)
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    clear();
    Node< T >* temp = other.head_;
    while (!temp)
    {
      push_back(temp->data_);
      temp = temp->next_;
    }
    return *this;
  }

  template< typename T >
  List< T >& List< T >::operator=(List< T >&& other)
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    return *this;
  }

  template< typename T >
  T& List< T >::operator[](size_t pos)
  {
    Iterator< T > iter(head_);
    return iter[pos].data_;
  }

  template< typename T >
  bool List< T >::empty()
  {
    return !head_;
  }

  template< typename T >
  void List< T >::clear()
  {
    while (head_)
    {
      Node< T >* temp = head_->next_;
      delete head_;
      head_ = temp;
    }
    head_ = nullptr;
    tail_ = nullptr;
  }

  template< typename T >
  void List< T >::push_back(const T& data)
  {
    Node< T >* pushNode = new Node< T >(data, tail_, nullptr);
    if (!head_)
    {
      head_ = pushNode;
      tail_ = pushNode;
    }
    else
    {
      tail_->next_ = pushNode;
      tail_ = pushNode;
    }
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    Node< T >* pushNode = new Node< T >(data, nullptr, head_);
    if (!head_)
    {
      head_ = pushNode;
      tail_ = pushNode;
    }
    else
    {
      head_->prev_ = pushNode;
      head_ = pushNode;
    }
  }

  template< typename T >
  void List< T >::pop_back()
  {
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      Node< T >* temp = tail_->prev_;
      delete tail_;
      tail_ = temp;
    }
  }

  template< typename T >
  void List< T >::pop_front()
  {
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      Node< T >* temp = head_->next_;
      delete head_;
      head_ = temp;
    }
  }

}

#endif

