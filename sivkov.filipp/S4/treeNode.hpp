#ifndef TREENODE_HPP
#define TREENODE_HPP

template <typename Key, typename Value>
struct TreeNode
{
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
  std::pair< Key, Value > data;

  TreeNode():
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    data(std::pair< Key, Value >())
  {}

  TreeNode(const Key& key, const Value& value):
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    data(std::make_pair(key, value))
  {}

  ~TreeNode() = default;
};


#endif
