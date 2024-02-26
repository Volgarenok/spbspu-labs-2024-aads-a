#include "node.hpp"

template < typename T >
Node< T >::Node():
  value(0),
  nextPtr(nullptr)
{};

template < typename T >
Node< T >::Node(const T & el):
  value(el),
  nextPtr(nullptr)
{};
