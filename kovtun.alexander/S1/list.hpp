#ifndef LIST_HPP
#define LIST_HPP

#include <cassert>

#include "const_iterator.hpp"

namespace kovtun
{
  template< typename T >
  class List
  {
  public:
    List();
    ~List();

    ConstIterator< T > cbegin() const;
    ConstIterator< T > cend() const;

    bool empty();

    void push_front(const T &);
    void push_back(const T &);
    void pop_front();
    void pop_back();
    void clear();
    void swap(List< T > & list);
    size_t size() const;

  private:
    Node< T > * head_;
    Node< T > * tail_;

    size_t size_;
  };

  template< typename T >
  List< T >::List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
  {}

  template< typename T >
  List< T >::~List()
  {
    while (head_)
    {
      pop_front();
    }
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const
  {
    return ConstIterator< T >(tail_);
  }

  template< typename T >
  void List< T >::push_front(const T & node)
  {
    
  }

  template< typename T >
  void List< T >::push_back(const T & node)
  {
   // TODO: first
  }

  template< typename T >
  void List< T >::pop_front()
  {
    // TODO: first
  }

  template< typename T >
  void List< T >::pop_back()
  {

  }

  template< typename T >
  bool List< T >::empty()
  {
    return size_ == 0;
  }

  template< typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template< typename T >
  void List< T >::swap(List< T > & list)
  {
    std::swap(list.head_, head_);
    std::swap(list.tail_, tail_);
    std::swap(list.size_, size_);
  }

  template< typename T >
  size_t List< T >::size() const
  {
    return size_;
  }
}

#endif
