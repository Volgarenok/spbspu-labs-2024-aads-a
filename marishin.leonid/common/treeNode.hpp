#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <algorithm>
#include <utility>

namespace marishin
{
  namespace detail
  {
    template< typename Key, typename Value >
    struct TreeNode
    {
      std::pair< Key, Value > data;
      TreeNode* left;
      TreeNode* right;
      TreeNode* parent;
      int height;

      TreeNode(const Key& key, const Value& val, TreeNode* parent):
        data(std::pair< Key, Value >(key, val)),
        left(nullptr),
        right(nullptr),
        parent(parent),
        height(0)
      {}

      TreeNode(const Key& key, const Value& val):
        data(std::pair< Key, Value >(key, val)),
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        height(0)
      {}

      TreeNode* rotateLeft(TreeNode** root)
      {
        TreeNode* newRoot = this->right;
        this->right = newRoot->left;
        if (newRoot->left)
        {
          newRoot->left->parent = this;
        }
        newRoot->parent = this->parent;
        if (this->isRoot())
        {
          *root = newRoot;
        }
        else
        {
          auto& child = this->isLeft() ? this->parent->left : this->parent->right;
          child = newRoot;
        }
        newRoot->left = this;
        this->parent = newRoot;
        this->height = this->height + 1 - std::min(newRoot->height, 0);
        newRoot->height = newRoot->height + 1 + std::max(this->height, 0);
        return newRoot;
      }


      TreeNode* rotateRight(TreeNode** root)
      {
        TreeNode* newRoot = this->left;
        this->left = newRoot->right;
        if (newRoot->right)
        {
          newRoot->right->parent = this;
        }
        newRoot->parent = this->parent;
        if (this->isRoot())
        {
          *root = newRoot;
        }
        else
        {
          auto& child = this->isLeft() ? this->parent->left : this->parent->right;
          child = newRoot;
        }
        newRoot->left = this;
        this->parent = newRoot;
        this->height = this->height + 1 - std::min(newRoot->height, 0);
        newRoot->height = newRoot->height + 1 + std::max(this->height, 0);
        return newRoot;
      }

      bool hasLeft() noexcept
      {
        return this->left != nullptr;
      }

      bool hasRight() noexcept
      {
        return this->right != nullptr;
      }

      bool isLeft() const noexcept
      {
        return this->parent && this->parent->left == this;
      }

      bool isRight() const noexcept
      {
        return this->parent && this->parent->right == this;
      }

      bool isRoot() const noexcept
      {
        return !this->parent;
      }

      bool isLeaf() const noexcept
      {
        return !(this->right || this->left);
      }

      bool hasAny() const noexcept
      {
        return this->right || this->left;
      }

      bool hasBoth() const noexcept
      {
        return this->right && this->left;
      }

    };
  }
}

#endif
