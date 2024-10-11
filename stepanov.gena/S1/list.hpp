#ifndef LIST_HPP
#define LIST_HPP

#include <utility>
#include <cstddef>
#include "node.hpp"

namespace stepanov
{
  template < typename T >
  class List
  {
  public:
    List();
    List(const List & other);
    List(List && other) noexcept;
    ~List();

    List & operator=(const List & other);
    List & operator=(List && other) noexcept;

    T & front();
    const T & front() const;
    bool empty() const noexcept;
    void push_front(const T & value);
    void push_front(T && value);
    void push_back(const T & value);
    void pop_front();
    void clear() noexcept;
    void swap(List & fwdlst);

    void remove(const T & value);
    template < typename Predicate >
    void remove_if(Predicate pred);
    void assign(size_t n, const T & value);

  private:
    Node<T> * head_;
    Node<T> * tail_;
  };

  template < typename T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}

  template <  typename T >
  T & List< T >::front()
  {
    return head_->data_;
  }

  template < typename T >
  const T & List< T >::front() const
  {
    return head_->data_;
  }

  template < typename T >
  bool List< T >::empty() const noexcept
  {
    return head_ == nullptr;
  }

  template < typename T >
  void List< T >::push_front(const T & value)
  {
    Node< T > * newnode = new Node< T >(value);
    newnode->next_ = head_;
    head_ = newnode;
    if (tail_ == nullptr)
    {
      tail_ = newnode;
    }
  }

  template < typename T >
  void List< T >::push_front(T && value)
  {
    Node< T > * newnode = new Node< T >(std::move(value));
    newnode->next_ = head_;
    head_ = newnode;
    if (tail_ == nullptr)
    {
      tail_ = newnode;
    }
  }

  template < typename T >
  void List< T >::push_back(const T & value)
  {
    Node< T > * newnode = new Node< T >(value);
    if (empty())
    {
      head_ = newnode;
      tail_ = newnode;
      return;
    }
    tail_->next_ = newnode;
    tail_ = newnode;
  }

  template < typename T >
  void List< T >::pop_front()
  {
    if (head_ == nullptr)
    {
      return;
    }
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
      return;
    }
    Node< T > * newhead = head_->next_;
    delete head_;
    head_ = newhead;
  }

  template < typename T >
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template < typename T >
  void List< T >::swap(List< T > & list)
  {
    Node< T > * subhead = head_;
    Node< T > * subtail = tail_;
    head_ = list.head_;
    tail_ = list.tail_;
    list.head_ = subhead;
    list.tail_ = subtail;
  }

}


#endif

