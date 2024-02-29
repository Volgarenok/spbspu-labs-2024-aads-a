#ifndef BILISTNODE_HPP
#define BILISTNODE_HPP

namespace rebdev
{
  template < class T >
  struct biListNode
  {
    T data_;
    biListNode * last_;
    biListNode * next_;
  };
}

#endif
