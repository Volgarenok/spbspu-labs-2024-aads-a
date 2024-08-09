#ifndef TREE
#define TREE
#include "iterator.hpp"

namespace baranov
{
  template< typename Key, typename T, typename Compare >
  class Tree
  {
  public:
    using iterator_t = Iterator< Key, T, Compare >;
  private:
    Node< Key, T > * root_;
    size_t size_;
  };
}

#endif

