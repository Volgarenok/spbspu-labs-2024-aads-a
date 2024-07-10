#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "node.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

namespace vyzhanov
{
  template<typename T>
  struct List
  {
    using citerator = ConstBiIterator< T >;
    using iterator = BiIterator< T >;

    List();
    ~List();
    void clear();
    bool empty();
  private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_
  };

  template< class T >
  List< T >::List() :
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T>
  void List<T>::clear()
  {
    while (head_ != tail_)
    {
      Node< T > newHead = head_->next_;
      delete head_;
      head_ = newHead;
    }
  }

  template < typename T>
  bool List<T>::empty()
  {
    return (head_ = tail_);
  }

}
#endif
