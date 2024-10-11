#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <memory>
#include "node.hpp"

namespace sakovskaia
{
  template< typename Key, typename T, typename Compare >
  class Tree;

  template< typename Key, typename T >
  struct Iterator
  {
    friend class Tree< Key, T, std::less< Key > >;
    public:
      Iterator(const Iterator< Key, T >& val):
        node_(val.node_)
      {}
  };
}

#endif
