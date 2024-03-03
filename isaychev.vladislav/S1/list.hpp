#ifndef LIST_HPP
#define LIST_HPP

#include "iterator.hpp"
#include "cIterator.hpp"

namespace isaychev
{
  template < typename T >
  class List
  {
    using iter = fwdIterator< T >;
    using cIter = cFwdIterator< T >;
   public:
    List();
    ~List();

    iter begin();
    cIter begin() const;
    iter end();
    cIter end() const;

    T & front();
    const T & front() const;
    bool empty();
    void push(const T & obj);
    void pop();
    void clear();
    void swap(List< T > & rhs);

   private:
    node_t< T > * head_;
  };

  template < typename T >
  List< T >::List():
    head_(nullptr)
  {}

  template < typename T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T >
  fwdIterator< T > List< T >::begin()
  {
    return fwdIterator< T >(head_);
  }

  template < typename T >
  cFwdIterator< T > List< T >::begin() const
  {
    return cFwdIterator< T >(head_);
  }

  template < typename T >
  fwdIterator< T > List< T >::end()
  {
    return fwdIterator< T >(nullptr);
  }

  template < typename T >
  cFwdIterator< T > List< T >::end() const
  {
    return cFwdIterator< T >(nullptr);
  }

  template < typename T >
  T & List< T >::front()
  {
    return head_->data;
  }

  template < typename T >
  const T & List< T >::front() const
  {
    return head_->data;
  }

  template < typename T >
  bool List< T >::empty()
  {
    return (head_ == nullptr);
  }

  template < typename T >
  void List< T >::push(const T & obj)
  {
    if (empty())
    {
      head_ = new node_t< T >{obj, nullptr};
    }
    else
    {
      node_t< T > * temp = head_->next;
      while (temp != nullptr)
      {
        temp = temp->next;
      }
      temp = new node_t< T >{obj, nullptr};
    }
  }

  template < typename T >
  void List< T >::pop()
  {
    if (!empty())
    {
      node_t< T > * temp = head_->next;
      delete head_;
      head_ = temp;
    }
  }

  template < typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop();
    }
  }

  template < typename T >
  void List< T >::swap(List< T > & rhs)
  {
    /*node_t< T > * tempHead = head_;
    head_ = rhs.head_;
    rhs.head_ = tempHead;*/
    std::swap(head_, rhs.head);
  }
}

#endif
