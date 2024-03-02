#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <utility>

namespace isaychev
{
  template < typename T >
  struct node_t
  {
    T data;
    node_t< T > * next;
  };

  template < typename T >
  class fwdIterator
  {
    using this_t = fwdIterator< T >;

   public:
    fwdIterator();
    fwdIterator(node_t< T > * pos);
    ~fwdIterator() = default;
    fwdIterator(const this_t & rhs) = default;
    this_t & operator=(const this_t & rhs) = default;
    fwdIterator(this_t && rhs) = default;
    this_t && operator=(this_t && rhs) = default;

    this_t & operator++();
    this_t & operator++(int);
    T & operator*();
    T * operator->();

   private:
    node_t< T > * currNode_;
  };

  template < typename T >
  fwdIterator< T >::fwdIterator():
    currNode_(nullptr)
  {}

  template < typename T >
  fwdIterator< T >::fwdIterator(node_t< T > * pos):
    currNode_(pos)
  {}

  template < typename T >
  fwdIterator< T > & fwdIterator< T >::operator++()
  {
    assert(currNode_!= nullptr);
    currNode_= currNode_->next;
    return *this;
  }

  template < typename T >
  fwdIterator< T > & fwdIterator< T >::operator++(int)
  {
    this_t res(*this);
    ++(*this);
    return res;
  }

  template < typename T >
  T & fwdIterator< T >::operator*()
  {
    return currNode_->data;
  }

  template < typename T >
  T * fwdIterator< T >::operator->()
  {
    return std::addressof(currNode_->data);
  }
}

#endif
