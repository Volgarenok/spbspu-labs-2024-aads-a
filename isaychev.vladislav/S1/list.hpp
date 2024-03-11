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
    List(const List< T > & rhs);
    List(const List< T > && rhs);
    List< T > & operator=(const List< T > & rhs);
    List< T > & operator=(const List< T >&& rhs);

    iter begin();
    cIter сbegin() const;
    iter end();
    cIter сend() const;

    T & front();
    const T & front() const;
    bool empty();
    void push(const T & obj);
    void pop();
    void clear();
    void swap(List< T > & rhs);
    void reverse();

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
  void copyList(const List< T > & list, const List< T > & rhs)
  {
    for (auto i = rhs.begin(); i != rhs.end(); ++i)
    {
      list.push(*i);
    }
  }

  template < typename T >
  List< T >::List(const List< T > & rhs)
  {
    copyList(*this, rhs);
  }

  template < typename T >
  List< T >::List(const List< T > && rhs):
    head_(rhs.head_)
  {
    rhs.head_ = nullptr;
  }

  template < typename T >
  List< T > & List< T >::operator=(const List< T > & rhs)
  {
    if (this != std::addressof(rhs))
    {
      this->clear();
      copyList(*this, rhs);
    }
  }

  template < typename T >
  List< T > & List< T >::operator=(const List< T > && rhs)
  {
    if (this != std::addressof(rhs))
    {
      this->clear();
      head_ = rhs.head_;
      rhs.head_ = nullptr;
    }
  }

  template < typename T >
  fwdIterator< T > List< T >::begin()
  {
    return fwdIterator< T >(head_);
  }

  template < typename T >
  cFwdIterator< T > List< T >::сbegin() const
  {
    return cFwdIterator< T >(head_);
  }

  template < typename T >
  fwdIterator< T > List< T >::end()
  {
    return fwdIterator< T >(nullptr);
  }

  template < typename T >
  cFwdIterator< T > List< T >::сend() const
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
    node_t< T > * temp = new node_t< T >(obj);
    temp->next = head_;
    head_ = temp;
  }

  template < typename T >
  void List< T >::pop()
  {
    if (head_)
    {
      node_t< T > * temp = head_->next;
      delete head_;
      head_ = temp;
    }
  }

  template < typename T >
  void List< T >::clear()
  {
    while (head_)
    {
      pop();
    }
  }

  template < typename T >
  void List< T >::swap(List< T > & rhs)
  {
    std::swap(head_, rhs.head);
  }

  template < typename T >
  void List< T >::reverse()
  {
    if (head_)
    {
      node_t< T > * currElem = head_;
      node_t< T > * temp1 = nullptr;
      node_t< T > * temp2 = head_;
      while (currElem)
      {
        temp2 = currElem->next;
        currElem->next = temp1;
        temp1 = currElem;
        currElem = temp2;
      }
      head_ = temp1;
    }
  }
}

#endif
