#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <functional>
#include <utility>

namespace piyavkin
{
  namespace detail
  {
    template< class Key, class T >
    struct TreeNode
    {
      template< class... Args >
      TreeNode(const Key& key, TreeNode* right, TreeNode* left, TreeNode* parent, Args&& ...args):
        val_type(key, std::forward< Args >(args)...),
        right_(right),
        left_(left),
        parent_(parent)
      {}
      std::pair< Key, T > val_type;
      TreeNode* right_;
      TreeNode* left_;
      TreeNode* parent_;
    };
  }
}
#endif
