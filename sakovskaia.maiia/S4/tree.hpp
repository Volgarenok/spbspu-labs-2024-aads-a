#ifndef TREE_HPP
#define TREE_HPP
#include "node.hpp"

namespace sakovskaia
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class Tree
  {
    using node_t = detail::Node< Key, Value >;
    using iterator = Iterator< Key, Value >;
    using const_iterator = ConstIterator< Key, Value >;
    public:
      Tree():
        root_(nullptr),
        size_(0),
        compare_(Compare())
      {}
  };
}

#endif
