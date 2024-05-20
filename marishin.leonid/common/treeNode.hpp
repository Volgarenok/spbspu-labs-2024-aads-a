#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>

namespace marishin
{
  namespace detail
  {
    template< class Key, class Value >
    struct TreeNode
    {
      using node_t = detail::TreeNode< Key, Value >;
      std::pair< Key, Value > data;
      node_t * parent;
      node_t * left;
      node_t * right;
      int height;
      TreeNode(const Key & key, const Value & value)
      {
        data = std::make_pair(key, value);
        height = 0;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
      }
      TreeNode(const Key & key, const Value & value, TreeNode * newParent)
      {
        data = std::make_pair(key, value);
        parent = newParent;
        left = nullptr;
        right = nullptr;
        height = 0;
      }
      bool isLeftChild() const
      {
        return (this->parent) && (this->parent->left == this);
      }
      bool isRightChild() const
      {
        return (this->parent) && (this->parent->right == this);
      }
      bool isRoot() const
      {
        return !this->parent;
      }
    };
  }
}

#endif
