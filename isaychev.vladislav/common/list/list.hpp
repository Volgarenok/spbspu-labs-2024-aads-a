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
    List(List< T > && rhs) noexcept;
    List(const List< T > & rhs);
    List< T > & operator=(List< T >&& rhs) noexcept;
    List< T > & operator=(const List< T > & rhs);

    iter begin() noexcept;
    iter end() noexcept;
    cIter begin() const noexcept;
    cIter end() const noexcept;
    cIter сbegin() const noexcept;
    cIter сend() const noexcept;

    T & front() noexcept;
    const T & front() const noexcept;
    T & back() noexcept;
    const T & back() const noexcept;
    void push_front(const T & obj);
    void pop_front();
    void push_back(const T & obj);

    bool empty() const noexcept;
    void clear();
    void swap(List< T > & rhs) noexcept;
    void reverse() noexcept;

   private:
    detail::node_t< T > * head_;
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
  List< T >::List(List< T > && rhs) noexcept:
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
  List< T > & List< T >::operator=(List< T > && rhs) noexcept
  {
    if (this != std::addressof(rhs))
    {
      this->clear();
      head_ = rhs.head_;
      rhs.head_ = nullptr;
    }
  }

  template < typename T >
  fwdIterator< T > List< T >::begin() noexcept
  {
    return fwdIterator< T >(head_);
  }

  template < typename T >
  fwdIterator< T > List< T >::end() noexcept
  {
    return fwdIterator< T >(nullptr);
  }

  template < typename T >
  CFwdIterator< T > List< T >::begin() const noexcept
  {
    return CFwdIterator< T >(head_);
  }

  template < typename T >
  CFwdIterator< T > List< T >::end() const noexcept
  {
    return CFwdIterator< T >(nullptr);
  }

  template < typename T >
  CFwdIterator< T > List< T >::сbegin() const noexcept
  {
    return CFwdIterator< T >(head_);
  }

  template < typename T >
  CFwdIterator< T > List< T >::сend() const noexcept
  {
    return CFwdIterator< T >(nullptr);
  }

  template < typename T >
  T & List< T >::front() noexcept
  {
    return head_->data;
  }

  template < typename T >
  const T & List< T >::front() const noexcept
  {
    return head_->data;
  }

  template < typename T >
  detail::node_t< T > * traverse_to_last(detail::node_t< T > * head)
  {
    while (head->next)
    {
      head = head->next;
    }
    return head;
  }

  template < typename T >
  T & List< T >::back() noexcept
  {
    detail::node_t< T > * last = traverse_to_last(head_);
    return last->data;
  }

  template < typename T >
  const T & List< T >::back() const noexcept
  {
    detail::node_t< T > * last = traverse_to_last(head_);
    return last->data;
  }

  template < typename T >
  bool List< T >::empty() const noexcept
  {
    return (head_ == nullptr);
  }

  template < typename T >
  void List< T >::push_front(const T & obj)
  {
    detail::node_t< T > * temp = new detail::node_t< T >(obj);
    temp->next = head_;
    head_ = temp;
  }

  template < typename T >
  void List< T >::pop_front()
  {
    if (head_)
    {
      detail::node_t< T > * temp = head_->next;
      delete head_;
      head_ = temp;
    }
    else
    {
      throw std::out_of_range("no more elements in list");
    }
  }

  template < typename T >
  void List< T >::push_back(const T & obj)
  {
    if (head_)
    {
      detail::node_t< T > * last = traverse_to_last(head_);
      last->next = new detail::node_t< T >(obj);
    }
    else
    {
      head_ = new detail::node_t< T >(obj);
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
  void List< T >::swap(List< T > & rhs) noexcept
  {
    std::swap(head_, rhs.head_);
  }

  template < typename T >
  void List< T >::reverse() noexcept
  {
    if (head_)
    {
      detail::node_t< T > * currElem = head_;
      detail::node_t< T > * temp1 = nullptr;
      detail::node_t< T > * temp2 = head_;
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
