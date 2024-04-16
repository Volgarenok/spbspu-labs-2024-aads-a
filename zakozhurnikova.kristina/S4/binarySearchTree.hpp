#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include "treeNode.hpp"
#include <cstddef>

namespace zakozhurnikova
{
  template< typename Key, typename Value >
  struct BinarySearchTree {
    BinarySearchTree() = default;

    int length()
    {
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
            this->put(key, val, currentNode->rightChild);
        }
        else
        {
          currentNode->rightChild = new TreeNode< Key, Value >(key, val, currentNode);
        }
      }
    }

    Value get(Key key)
    {
      if (this->root)
      {
        TreeNode< Key, Value >* res = this->get(key, this->root);
        if (res)
        {
          return res->value;
        }
        else
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }

    TreeNode< Key, Value >* get(Key key, TreeNode< Key, Value >* currentNode)
    {
      if (!currentNode)
      {
        return nullptr;
      }
      else if (currentNode->key == key)
      {
        return currentNode;
      }
      else if (key < currentNode->key)
      {
        return this->get(key, currentNode->leftChild);
      }
      else
      {
        return this->get(key, currentNode->rightChild);
      }
    }

  private:
    TreeNode< Key, Value >* root;
    size_t size;
  };
}

#endif
