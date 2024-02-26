#include "iterator.hpp"

#include <stdexcept>
#include "node.hpp"

// template < class T >
// using iterator_l = arakelyan::Iterator< T >;

template < class T >
Iterator< T >::Iterator():
  node(nullptr)
{}

template < class T >
Iterator< T > & Iterator< T >::operator++()
{
  if (node == nullptr)
  {
    throw std::logic_error("node == nullptr!");
  }
  node = node->nextPtr;
  return *this;
}

template < class T >
Iterator< T > Iterator< T >::operator++(int)
{
  if (node == nullptr)
  {
    throw std::logic_error("node == nullptr!");
  }
  Iterator< T > res(*this);
  ++(*this);
  return res;
}

template < class T >
T & Iterator< T >::operator*()
{
  if (node == nullptr)
  {
    throw std::logic_error("node == nullptr");
  }
  return node->value;
}

template < class  T >
T * Iterator< T >::operator->()
{
  if (node == nullptr)
  {
    throw std::logic_error("node == nullptr");
  }
  return std::addressof(*this);
}


template < class T >
bool Iterator< T >::operator!=(const Iterator< T > & val) const
{
  return node == val.node;
}

template < class T >
bool Iterator< T >::operator==(const Iterator< T > & val) const
{
  return !(val == *this);
}
