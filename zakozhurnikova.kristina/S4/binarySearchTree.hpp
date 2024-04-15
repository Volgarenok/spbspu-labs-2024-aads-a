#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include "treeNode.hpp"
#include <cstddef>

namespace zakozhurnikova
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree {
    BinarySearchTree() {
      this->root = nullptr;
      this->size = 0;
    }

    int length() {
      return this->size;
    }

    void push(Key key, Value val)
    {
      if (this->root)
      {
        this->put(key, val, this->root);
      }
      else
      {
        this->root = new TreeNode< Key, Value >(key, val);
      }
      this->size = this->size + 1;
    }

    void put(Key key, Value val, TreeNode< Key, Value >* currentNode)
    {
      if (key < currentNode->key)
      {
        if (currentNode->hasLeftChild())
        {
          this->put(key, val, currentNode->leftChild);
        }
        else
        {
          currentNode->leftChild = new TreeNode< Key, Value >(key, val, currentNode);
        }
      }
      else
      {
        if (currentNode->hasRightChild()){
            this->_put(key, val, currentNode->rightChild);
        }
        else
        {
          currentNode->rightChild = new TreeNode< Key, Value >(key, val, currentNode);
        }
      }
    }
  private:
    TreeNode< Key, Value >* root;
    size_t size;
  };
}

#endif
