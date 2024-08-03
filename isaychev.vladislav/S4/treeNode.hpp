#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <utility>

namespace isaychev
{
  namespace detail
  {
    template < class Key, class Value >
    struct TreeNode
    {
      std::pair< Key, Value > data;
      TreeNode< Key, Value > * right;
      TreeNode< Key, Value > * left;
      TreeNode< Key, Value > * parent;

      TreeNode (Key key, Value value, TreeNode< Key, Value > * root):
       data(key, value),
       right(nullptr),
       left(nullptr),
       parent(root)
      {}
    };
  }
}

#endif
