#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <utility>

namespace gladyshev
{
  namespace detail
  {
    template< typename Key, typename Value >
    struct TNode
    {
      std::pair< Key, Value > data;
      TNode* right;
      TNode* left;
      TNode* parent;
      long long height;
      TNode(const Key& key, const Value& value):
        data(std::make_pair(key, value)),
        right(nullptr),
        left(nullptr),
        parent(nullptr),
        height(0)
      {}
    };
  }
}

#endif
