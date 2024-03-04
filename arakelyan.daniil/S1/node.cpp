#include "node.hpp"

template < class T >
Node< T >::Node():
  value(0),
  nextNode(nullptr),
  prevNode(nullptr)
{}

template < class T >
Node< T >::Node(const T &val, Node< T > *next, Node< T > *prev):
  value(val),
  nextNode(next),
  prevNode(prev)
{}

template < class T >
Node< T >::Node(const T &el):
  value(el),
  nextNode(nullptr),
  prevNode(nullptr)
{}
