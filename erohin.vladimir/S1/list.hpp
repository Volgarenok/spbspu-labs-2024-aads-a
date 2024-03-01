#ifndef LIST_HPP
#define LIST_HPP

#include <initializer_list>
#include "node.hpp"
#include "list_iterator.hpp"

namespace erohin
{
  template< class T >
  class List
  {
  public:
    using iterator = ListIterator< T >;
    List();
    List(const List & list);
    List(List && list) noexcept;
    ~List();
    void insert(const T & value);
    iterator begin();
    iterator end();
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
  {}

  template< class T >
  List< T >::List(List< T > && list) noexcept:
    head_(list.head_)
  {
    list.head_ = nullptr;
  }

  template< class T >
  List< T >::~List()
  {
    while (head_)
    {
      Node< T > * new_head = head_->next_;
      delete head_;
      head_ = new_head;
    }
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
  void List< T >::insert(const T & value)
  {
    Node< T > * elem = new Node< T >(value, head_);
    head_ = elem;
  }
}

#endif
