#ifndef NODE_HPP
#define NODE_HPP

namespace baranov
{
  template< class T >
  struct Node
  {
    T data_;
    Node * next_;
    Node * prev_;
  };
}

#endif
