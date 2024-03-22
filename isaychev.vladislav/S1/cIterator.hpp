#ifndef CITERATOR_HPP
#define CITERATOR_HPP

#include <stdexcept>
#include <utility>
#include "node.hpp"

namespace isaychev
{
  template < typename T >
  class CFwdIterator
  {
    using this_t = CFwdIterator< T >;

   public:
    CFwdIterator();
    CFwdIterator(nodeNS::node_t< T > * pos);

    this_t operator++();
    this_t operator++(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;

   private:
    nodeNS::node_t< T > * currNode_;
  };

  template < typename T >
  CFwdIterator< T >::CFwdIterator():
   currNode_(nullptr)
  {}

  template < typename T >
  CFwdIterator< T >::CFwdIterator(nodeNS::node_t< T > * pos):
   currNode_(pos)
  {}

  template < typename T >
  CFwdIterator< T > CFwdIterator< T >::operator++()
  {
    currNode_ = currNode_->next;
    return *this;
  }

  template < typename T >
  CFwdIterator< T > CFwdIterator< T >::operator++(int)
  {
    this_t res(*this);
    ++(*this);
    return res;
  }

  template < typename T >
  const T & CFwdIterator< T >::operator*() const
  {
    return currNode_->data;
  }

  template < typename T >
  const T * CFwdIterator< T >::operator->() const
  {
    return std::addressof(currNode_->data);
  }

  template < typename T >
  bool CFwdIterator< T >::operator==(const this_t & rhs) const
  {
    return (currNode_ == rhs.currNode_);
  }

  template < typename T >
  bool CFwdIterator< T >::operator!=(const this_t & rhs) const
  {
    return !(currNode_ == rhs.currNode_);
  }
}

#endif
