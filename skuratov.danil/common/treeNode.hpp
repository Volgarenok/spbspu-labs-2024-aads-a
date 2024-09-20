#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>

namespace skuratov
{
  namespace detail
  {
    template < typename Key, typename Value >
    struct TreeNode
    {
      TreeNode(const Key& key, const Value& value):
        parent_(nullptr),
        left_(nullptr),
        right_(nullptr),
        data_(std::make_pair(key, value))
      {}
      ~TreeNode() = default;
      TreeNode* parent_;
      TreeNode* left_;
      TreeNode* right_;
      std::pair< Key, Value > data_;
    };
  }
}

#endif
