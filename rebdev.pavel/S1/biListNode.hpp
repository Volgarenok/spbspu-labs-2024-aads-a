#ifndef BILISTNODE_HPP
#define BILISTNODE_HPP

namespace rebdev
{
  template < class T >

  struct biListNode
  {
    T data;
    biListNode * last;
    biListNode * next;
  };
}

#endif
