#ifndef TREENODE_HPP
#define TREENODE_HPP

namespace zakozhurnikova
{
  template< typename Key, typename Value >
  struct TreeNode {

    Key key;
    Value value;
    TreeNode *leftChild;
    TreeNode *rightChild;
    TreeNode *parent;

    TreeNode(Key key, Value val, TreeNode *parent = nullptr, TreeNode *left = nullptr, TreeNode *right = nullptr)
    {
      this->key = key;
      this->value = val;
      this->leftChild = left;
      this->rightChild = right;
      this->parent = parent;
    }

    TreeNode* hasLeftChild()
    {
      return this->leftChild;
    }

    TreeNode *hasRightChild()
    {
      return this->rightChild;
    }

    bool isLeftChild()
    {
      return this->parent && this->parent->leftChild == this;
    }

    bool isRightChild()
    {
      return this->parent && this->parent->rightChild == this;
    }

    bool isRoot()
    {
      return !this->parent;
    }

    bool isLeaf()
    {
      return !(this->rightChild || this->leftChild);
    }

    bool hasAnyChildren()
    {
      return this->rightChild || this->leftChild;
    }

    bool hasBothChildren()
    {
      return this->rightChild && this->leftChild;
    }
  };
}

#endif
