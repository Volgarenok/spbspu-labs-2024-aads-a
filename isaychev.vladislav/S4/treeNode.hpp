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

      TreeNode(const std::pair< Key, Value > & new_data, TreeNode< Key, Value > * root):
       data(new_data),
       right(nullptr),
       left(nullptr),
       parent(root)
      {}
    };
  }
}

#endif
