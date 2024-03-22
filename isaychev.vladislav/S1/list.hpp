#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include "iterator.hpp"
#include "cIterator.hpp"

namespace isaychev
{
  template < typename T >
  class List
  {
    using iter = fwdIterator< T >;
    using cIter = CFwdIterator< T >;

   public:
    List();
    ~List();
    List(List< T > && rhs);
    List(const List< T > & rhs);
    List< T > & operator=(List< T >&& rhs);
    List< T > & operator=(const List< T > & rhs);

    iter begin();
    iter end();
    cIter begin() const;
    cIter end() const;
    cIter сbegin() const;
    cIter сend() const;

    T & front();
    const T & front() const;
    bool empty();
    void push_front(const T & obj);
    void pop_front();
    void clear();
    void swap(List< T > & rhs);
    void reverse();

   private:
    nodeNS::node_t< T > * head_;
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
  List< T >::List(const List< T > & rhs):
   head_(nullptr)
  {
    for (auto i = rhs.begin(); i != rhs.end(); ++i)
    {
      this->push_front(*i);
    }
  }

  template < typename T >
  List< T >::List(List< T > && rhs):
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
      for (auto i = rhs.begin(); i != rhs.end(); ++i)
      {
        this->push_front(*i);
      }
    }
  }

  template < typename T >
  List< T > & List< T >::operator=(List< T > && rhs)
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
  fwdIterator< T > List< T >::end()
  {
    return fwdIterator< T >(nullptr);
  }

  template < typename T >
  CFwdIterator< T > List< T >::begin() const
  {
    return CFwdIterator< T >(head_);
  }

  template < typename T >
  CFwdIterator< T > List< T >::end() const
  {
    return CFwdIterator< T >(nullptr);
  }

  template < typename T >
  CFwdIterator< T > List< T >::сbegin() const
  {
    return CFwdIterator< T >(head_);
  }

  template < typename T >
  CFwdIterator< T > List< T >::сend() const
  {
    return CFwdIterator< T >(nullptr);
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
  void List< T >::push_front(const T & obj)
  {
    nodeNS::node_t< T > * temp = new nodeNS::node_t< T >(obj);
    temp->next = head_;
    head_ = temp;
  }

  template < typename T >
  void List< T >::pop_front()
  {
    if (head_)
    {
      nodeNS::node_t< T > * temp = head_->next;
      delete head_;
      head_ = temp;
    }
    else
    {
      throw std::out_of_range("no more elements in list");
    }
  }

  template < typename T >
  void List< T >::clear()
  {
    while (head_)
    {
      pop_front();
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
      nodeNS::node_t< T > * currElem = head_;
      nodeNS::node_t< T > * temp1 = nullptr;
      nodeNS::node_t< T > * temp2 = head_;
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
