#ifndef MYTREE_HPP
#define MYTREE_HPP

#include "treeNode.hpp"

namespace rebdev
{
  template < class T >
  class tree
  {
    using node = treeNode< T >;

    public:
      tree():
        node_(new node{nullptr, nullptr, nullptr, T{}})
      {}
      ~tree()
      {
        delete node_;
      }
    private:
      node * node_;
  };
}

#endif
