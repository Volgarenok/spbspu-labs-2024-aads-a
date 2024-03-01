#ifndef LIST_HPP
#define LIST_HPP

#include <initializer_list>
#include <stdexcept>
#include "node.hpp"
#include "list_iterator.hpp"
#include "list_const_iterator.hpp"

namespace erohin
{
  template< class T >
  class List
  {
  public:
    using iterator = ListIterator< T >;
    using const_iterator = ListConstIterator< T >;
    List();
    List(const List & list);
    List(List && list) noexcept;
    List(size_t count, const T & value);
    List(std::initializer_list< T > init_list);
    template< class InputIt >
    List(InputIt first, InputIt last);
    ~List();
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    T & front();
    const T & front() const;
    bool empty() const;
    void push_front(const T & value);
    void pop_front();
    void clear();
    void swap(List< T > & list);
  private:
    Node< T > * head_;
  };

  template< class T >
  List< T >::List():
    head_(nullptr)
  {}

  template< class T >
  List< T >::List(const List< T > & list):
    head_(nullptr)
  {
    auto current_iter = list.begin();
    auto end_iter = list.end();
    while (current_iter != end_iter)
    {
      try
      {
        push_front(*(current_iter++));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  List< T >::List(List< T > && list) noexcept:
    head_(list.head_)
  {
    list.head_ = nullptr;
  }

  template< class T >
  List< T >::List(size_t count, const T & value):
    head_(nullptr)
  {
    for (size_t i = 0; i < count; ++i)
    {
      try
      {
        push_front(value);
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  List< T >::List(std::initializer_list< T > init_list):
    head_(nullptr)
  {
    auto init_begin = init_list.begin();
    auto init_end = init_list.end();
    while (init_begin != init_end)
    {
      try
      {
        push_front(*(init_begin++));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  template< class InputIt >
  List< T >::List(InputIt first, InputIt last):
    head_(nullptr)
  {
    while(first != last)
    {
      try
      {
        push_front(*(first++));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  ListIterator< T > List< T >::begin()
  {
    return ListIterator< T >(head_);
  }

  template< class T >
  ListIterator< T > List< T >::end()
  {
    return ListIterator< T >(nullptr);
  }

  template< class T >
  ListConstIterator< T > List< T >::begin() const
  {
    return ListConstIterator< T >(head_);
  }

  template< class T >
  ListConstIterator< T > List< T >::end() const
  {
    return ListConstIterator< T >(nullptr);
  }

  template< class T >
  ListConstIterator< T > List< T >::cbegin() const
  {
    return ListConstIterator< T >(head_);
  }

  template< class T >
  ListConstIterator< T > List< T >::cend() const
  {
    return ListConstIterator< T >(nullptr);
  }

  template< class T >
  T & List< T >::front()
  {
    return head_->data_;
  }

  template< class T >
  const T & List< T >::front() const
  {
    return head_->data_;
  }

  template< class T >
  bool List< T >::empty() const
  {
    return !head_;
  }

  template< class T >
  void List< T >::push_front(const T & value)
  {
    Node< T > * elem = new Node< T >(value, head_);
    head_ = elem;
  }

  template< class T >
  void List< T >::pop_front()
  {
    Node< T > * new_head = head_->next_;
    delete head_;
    head_ = new_head;
  }

  template< class T >
  void List< T >::clear()
  {
    while (head_)
    {
      pop_front();
    }
  }

  template< class T >
  void List< T >::swap(List< T > & list)
  {
    std::swap(head_, list.head_);
  }
}

#endif
