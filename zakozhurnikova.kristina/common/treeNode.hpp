#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <utility>
#include <algorithm>

namespace zakozhurnikova
{

  namespace detail
  {
    template < typename Key, typename Value >
    struct TreeNode
    {
      std::pair< Key, Value > data;
      TreeNode* leftChild;
      TreeNode* rightChild;
      TreeNode* parent;
      int balanceFactor;

      TreeNode(Key key, Value val, TreeNode* parent)
      {
        data.first = key;
        data.second = val;
        this->rightChild = nullptr;
        this->leftChild = nullptr;
        this->parent = parent;
        this->balanceFactor = 0;
      }

      TreeNode(Key key, Value val)
      {
        data.first = key;
        data.second = val;
        this->rightChild = nullptr;
        this->leftChild = nullptr;
        this->parent = nullptr;
        this->balanceFactor = 0;
      }

    TreeNode* rotateLeft()
    {
      TreeNode* newRoot = this->rightChild;
      this->rightChild = newRoot->leftChild;
      if (newRoot->leftChild != nullptr)
      {
        newRoot->leftChild->parent = this;
      }
      newRoot->parent = this->parent;
      if (!this->isRoot())
      {
        if (this->isLeftChild())
        {
          this->parent->leftChild = newRoot;
        }
        else
        {
          this->parent->rightChild = newRoot;
        }
      }
      newRoot->leftChild = this;
      this->parent = newRoot;
      this->balanceFactor = this->balanceFactor + 1 - std::min(newRoot->balanceFactor, 0);
      newRoot->balanceFactor = newRoot->balanceFactor + 1 + std::max(this->balanceFactor, 0);
      return newRoot;
    }

    TreeNode* rotateRight()
    {
      TreeNode* newRoot = this->leftChild;
      this->leftChild = newRoot->rightChild;
      if (newRoot->rightChild != nullptr)
      {
        newRoot->rightChild->parent = this;
      }
      newRoot->parent = this->parent;
      if (!this->isRoot())
      {
        if (this->isLeftChild())
        {
          this->parent->leftChild = newRoot;
        }
        else
        {
          this->parent->rightChild = newRoot;
        }
      }
      newRoot->rightChild = this;
      this->parent = newRoot;
      this->balanceFactor = this->balanceFactor - 1 - std::max(0, newRoot->balanceFactor);
      newRoot->balanceFactor = newRoot->balanceFactor - 1 + std::min(0, this->balanceFactor);
      return newRoot;
    }

      TreeNode* hasLeftChild() noexcept
      {
        return this->leftChild;
      }

      TreeNode* hasRightChild() noexcept
      {
        return this->rightChild;
      }

      bool isLeftChild() const noexcept
      {
        return this->parent && this->parent->leftChild == this;
      }

      bool isRightChild() const noexcept
      {
        return this->parent && this->parent->rightChild == this;
      }

      bool isRoot() const noexcept
      {
        return !this->parent;
      }

      bool isLeaf() const noexcept
      {
        return !(this->rightChild || this->leftChild);
      }

      bool hasAnyChildren() const noexcept
      {
        return this->rightChild || this->leftChild;
      }

      bool hasBothChildren() const noexcept
      {
        return this->rightChild && this->leftChild;
      }
    };
  }
}

#endif
