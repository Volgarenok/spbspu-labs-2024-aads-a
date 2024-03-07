#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "node.hpp"

namespace baranov
{
  template< class T >
  class Iterator
  {
    public:
      using this_t = Iterator< T >;

      Iterator();
      ~Iterator() = default;
      Iterator(const this_t &) = default;
      this_t & operator=(const this_t &) = default;

      this_t & operator++();
      this_t operator ++(int);
    private:
      Node< T > * node_;
  };

  template< class T >
  Iterator< T >::Iterator():
    node_(nullptr)
  {}

  template< class T >
  Iterator< T > & Iterator< T >::operator++()
  {
    Iterator temp = *this;
    ++(*this);
    return temp;
  }

  template< class T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    node_ = node_->next_;
    return * this;
  }
}

#endif

