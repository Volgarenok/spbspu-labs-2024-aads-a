#ifndef TREENODE_HPP
#define TREENODE_HPP

namespace rebdev
{
  template < class T >
  struct treeNode
  {
    treeNode * parent;
    treeNode * right;
    treeNode * left;
    T data;
  };
}

#endif
