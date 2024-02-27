#include "node.hpp"

template < typename T >
Node< T >::Node():
  value(0),
  nextNode(nullptr),
  prevNode(nullptr)
{};

template < typename T >
Node< T >::Node(const T &el):
  value(el),
  nextNode(nullptr),
  prevNode(nullptr)
{};
