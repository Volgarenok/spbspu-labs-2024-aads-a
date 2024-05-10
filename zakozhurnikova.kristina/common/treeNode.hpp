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
