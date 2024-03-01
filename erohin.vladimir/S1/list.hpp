#ifndef LIST_HPP
#define LIST_HPP

#include <initializer_list>
#include "node.hpp"

namespace erohin
{
  template< class T >
  class List
  {
  public:
    List();
    List(const List & list);
    List(List && list);
    ~List();
    void insert(const T & value);
    bool empty() const;
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
  List< T >::List(List< T > && list):
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
  void List< T >::insert(const T & value)
  {
    Node< T > * elem = new Node(value, head_);
    head_ = elem;
  }
}

#endif
