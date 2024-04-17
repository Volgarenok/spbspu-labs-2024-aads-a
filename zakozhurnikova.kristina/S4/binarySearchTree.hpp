#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include "treeNode.hpp"
#include <cstddef>
#include <iostream>

namespace zakozhurnikova
{
  template< typename Key, typename Value >
  struct BinarySearchTree {
    using node = TreeNode< Key, Value >;
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
        this->root = new node(key, val);
      }
      this->size = this->size + 1;
    }

    void put(Key key, Value val, node* currentNode)
    {
      if (key < currentNode->key)
      {
        if (currentNode->hasLeftChild())
        {
          this->put(key, val, currentNode->leftChild);
        }
        else
        {
          currentNode->leftChild = new node(key, val, currentNode);
        }
      }
      else
      {
        if (currentNode->hasRightChild()){
            this->put(key, val, currentNode->rightChild);
        }
        else
        {
          currentNode->rightChild = new node(key, val, currentNode);
        }
      }
    }

    Value get(Key key)
    {
      if (this->root)
      {
        node* res = this->get(key, this->root);
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

    node* get(Key key, node* currentNode)
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

    //херня какая-то пока что, сначала пробую балансировку при вставке
    void del(Key key)
    {
      if (this->size > 1)
      {
        node* nodeToRemove = this->get(key, this->root);
        if (nodeToRemove)
        {
          this->remove(nodeToRemove);
          this->size = this->size - 1;
        }
        else
        {
          std::cerr << "Error, key not in tree" << '\n';
        }
      }
      else if (this->size == 1 && this->root->key == key)
      {
        this->root = nullptr;
        this->size = this->size - 1;
      }
      else
      {
        std::cerr << "Error, key not in tree" << '\n';
      }
    }


  private:
    node* root;
    size_t size;
  };
}

#endif
