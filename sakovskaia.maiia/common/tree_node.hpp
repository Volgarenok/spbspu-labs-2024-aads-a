#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP
#include <utility>

namespace sakovskaia
{
  namespace detail
  {
    template < typename Key, typename Value >
    struct Node
    {
      Node * left;
      Node * right;
      Node * parent;
      std::pair< Key, Value > data;

      Node() :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(std::pair< Key, Value >())
      {}

      Node(const Key & key, const Value & value) :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(std::make_pair(key, value))
      {}
    };
  }
}

#endif
