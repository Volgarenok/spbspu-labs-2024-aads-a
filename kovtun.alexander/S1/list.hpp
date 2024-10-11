#ifndef LIST_HPP
#define LIST_HPP

#include "const_iterator.hpp"

namespace kovtun
{
  template< typename T >
  class List
  {
  public:
    List();
    ~List() = default;

    ConstIterator< T > cbegin() const;
    ConstIterator< T > cend() const;

    bool empty();

    void push_front(const T &);
    void push_back(const T &);
    void pop_front();
    void pop_back();
    void clear();
    void swap();

  private:
    Node< T > * head_;
    Node< T > * tail_;

    size_t size_;
  };

  template< typename T >
  List< T >::List() :
      head_(new Node< T >(T())),
      tail_(head_),
      size_(0)
  {}

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
}

#endif
