#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include "treeNode.hpp"
#include <algorithm>
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
          this->updateBalance(currentNode->leftChild);
        }
      }
      else
      {
        if (currentNode->hasRightChild())
        {
          this->put(key, val, currentNode->rightChild);
        }
        else
        {
          currentNode->rightChild = new node(key, val, currentNode);
          this->updateBalance(currentNode->rightChild);
        }
      }
    }

    void rebalance(node *node)
    {
      if (node->balanceFactor < 0)
      {
        if (node->rightChild->balanceFactor > 0)
        {
          this->rotateRight(node->rightChild);
          this->rotateLeft(node);
        }
        else
        {
          this->rotateLeft(node);
        }
      }
      else if (node->balanceFactor > 0)
      {
        if (node->leftChild->balanceFactor < 0)
        {
          this->rotateLeft(node->leftChild);
          this->rotateRight(node);
        }
        else
        {
          this->rotateRight(node);
        }
      }
    }

    void updateBalance(node* node)
    {
      if (node->balanceFactor > 1 || node->balanceFactor < -1)
      {
        this->rebalance(node);
        return;
      }
      if (node->parent != nullptr)
      {
        if (node->isLeftChild())
        {
          node->parent->balanceFactor += 1;
        }
        else if (node->isRightChild())
        {
          node->parent->balanceFactor -= 1;
        }
        if (node->parent->balanceFactor != 0)
        {
          this->updateBalance(node->parent);
        }
      }
    }

    void rotateLeft(node* rotRoot)
    {
      node* newRoot = rotRoot->rightChild;
      rotRoot->rightChild = newRoot->leftChild;
      if (newRoot->leftChild != nullptr)
      {
        newRoot->leftChild->parent = rotRoot;
      }
      newRoot->parent = rotRoot->parent;
      if (rotRoot->isRoot())
      {
        this->root = newRoot;
      }
      else
      {
        if (rotRoot->isLeftChild())
        {
          rotRoot->parent->leftChild = newRoot;
        }
        else
        {
          rotRoot->parent->rightChild = newRoot;
        }
      }
      newRoot->leftChild = rotRoot;
      rotRoot->parent = newRoot;
      rotRoot->balanceFactor = rotRoot->balanceFactor + 1 - std::min(newRoot->balanceFactor, 0);
      newRoot->balanceFactor = newRoot->balanceFactor + 1 + std::max(rotRoot->balanceFactor, 0);
    }

    void rotateRight(node *rotRoot)
    {
      node* newRoot = rotRoot->leftChild;
      rotRoot->leftChild = newRoot->rightChild;
      if (newRoot->rightChild != nullptr)
      {
        newRoot->rightChild->parent = rotRoot;
      }
      newRoot->parent = rotRoot->parent;
      if (rotRoot->isRoot())
      {
        this->root = newRoot;
      }
      else
      {
        if (rotRoot->isLeftChild())
        {
          rotRoot->parent->leftChild = newRoot;
        }
        else
        {
          rotRoot->parent->rightChild = newRoot;
        }
      }
      newRoot->rightChild = rotRoot;
      rotRoot->parent = newRoot;
      rotRoot->balanceFactor = rotRoot->balanceFactor - 1 - std::max(0, newRoot->balanceFactor);
      newRoot->balanceFactor = newRoot->balanceFactor - 1 + std::min(0, rotRoot->balanceFactor);
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
