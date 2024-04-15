#ifndef TREENODE_HPP
#define TREENODE_HPP

namespace zakozhurnikova
{
  template< typename Key, typename Value >
  struct TreeNode {

    Key key;
    Value payload;
    TreeNode *leftChild;
    TreeNode *rightChild;
    TreeNode *parent;
  };
}

#endif
