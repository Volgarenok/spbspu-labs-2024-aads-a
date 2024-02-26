#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "node.hpp"
#include "node.cpp"

template < class T >
struct Iterator
{
  Node< T > * node;
  // using iterator_l = Iterator< T >;

  Iterator();
  Iterator(const Iterator< T > & val) = default;
  Iterator< T > & operator=(const Iterator< T > & val) = default;

  Iterator< T > & operator++();
  Iterator< T > operator++(int);

  T & operator*();
  T * operator->();
  //+ const выше

  // operator--
  // operator--(int)

  bool operator!=(const Iterator< T > & val) const;
  bool operator==(const Iterator< T > & val) const;

  ~Iterator() = default;
};
#endif
