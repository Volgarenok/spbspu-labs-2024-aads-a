#ifndef CITERATOR_HPP
#define CITERATOR_HPP

#include <stdexcept>
#include <utility>
#include "node.hpp"

namespace isaychev
{
  template < typename T >
  class cFwdIterator
  {
    using this_t = cFwdIterator< T >;

   public:
    cFwdIterator();
    cFwdIterator(node_t< T > * pos);
    ~cFwdIterator() = default;
    cFwdIterator(const this_t & rhs) = default;
    this_t & operator=(const this_t & rhs) = default;

    this_t operator++();
    this_t operator++(int);
    const T & operator*();
    const T * operator->();
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;

   private:
    node_t< T > * currNode_;
  };

  template < typename T >
  cFwdIterator< T >::cFwdIterator():
    currNode_(nullptr)
  {}

  template < typename T >
  cFwdIterator< T >::cFwdIterator(node_t< T > * pos):
    currNode_(pos)
  {}

  template < typename T >
  cFwdIterator< T >  cFwdIterator< T >::operator++()
  {
    currNode_ = currNode_->next;
    return *this;
  }

  template < typename T >
  cFwdIterator< T >  cFwdIterator< T >::operator++(int)
  {
    this_t res(*this);
    ++(*this);
    return res;
  }

  template < typename T >
  const T & cFwdIterator< T >::operator*()
  {
    return currNode_->data;
  }

  template < typename T >
  const T * cFwdIterator< T >::operator->()
  {
    return std::addressof(currNode_->data);
  }

  template < typename T >
  bool cFwdIterator< T >::operator==(const this_t & rhs) const
  {
    return (currNode_ == rhs.currNode_);
  }

  template < typename T >
  bool cFwdIterator< T >::operator!=(const this_t & rhs) const
  {
    return !(currNode_ == rhs.currNode_);
  }
}

#endif
