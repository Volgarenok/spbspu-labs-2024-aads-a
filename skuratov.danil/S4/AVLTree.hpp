#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include "treeNode.hpp"
#include "constIteratorTree.hpp"

namespace skuratov
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLTree
  {
  public:
    AVLTree():
      root_(nullptr),
      cmp_(Compare()),
      size_(0)
    {}

    ~AVLTree()
    {
      clear();
    }

    AVLTree(const AVLTree& diff):
      root_(nullptr),
      cmp_(diff.cmp_),
      size_(0)
    {
      try
      {
        for (auto it = diff.cbegin(); it != diff.cend(); it++)
        {
          push(it->first, it->second);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    AVLTree& operator=(const AVLTree& diff)
    {
      if (this != std::addressof(diff))
      {
        AVLTree tempNode(diff);
        swap(tempNode);
      }
      return *this;
    }

    AVLTree(AVLTree&& diff) noexcept:
      root_(diff.root_),
      cmp_(diff.cmp_),
      size_(diff.size_)
    {
      diff.root_ = nullptr;
      diff.size_ = 0;
    }

    AVLTree& operator=(AVLTree&& diff) noexcept
    {
      if (this != std::addressof(diff))
      {
        clear();
        swap(diff);
      }
      return *this;
    }

    ConstIteratorTree cbegin() const noexcept
    {
      return ConstIteratorTree(root_);
    }

    ConstIteratorTree cend() const noexcept
    {
      return ConstIteratorTree(nullptr);
    }

    size_t size() const noexcept
    {
      return size_;
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    Value& at(const Key& key)
    {
      detail::TreeNode< Key, Value >* nodePointer = findNode(root_, key);

      if (!nodePointer)
      {
        throw std::out_of_range("Key not found");
      }
      return nodePointer->data_.second;
    }

    const Value& at(const Key& key) const
    {
      detail::TreeNode< Key, Value >* nodePointer = findNode(root_, key);

      if (!nodePointer)
      {
        throw std::out_of_range("Key not found");
      }
      return nodePointer->data_.second;
    }

    Value& operator[](const Key& key)
    {
      detail::TreeNode< Key, Value >* nodePointer = findNode(root_, key);

      if (nodePointer == nullptr)
      {
        nodePointer = insertNode(root_, key, Value());
      }
      return nodePointer->data_.second;
    }

    const Value& operator[](const Key& key) const
    {
      detail::TreeNode< Key, Value >* nodePointer = findNode(root_, key);

      if (nodePointer == nullptr)
      {
        throw std::out_of_range("Key not found");
      }
      return nodePointer->data_.second;
    }

    void clear() noexcept
    {
      removeNode(root_);
      root_ = nullptr;
      size_ = 0;
    }

    void swap(AVLTree& diff)
    {
      std::swap(root_, diff.root_);
      std::swap(cmp_, diff.cmp_);
      std::swap(size_, diff.size_);
    }

    ConstIteratorTree find(const Key& key) const
    {
      return ConstIteratorTree(findNode(root_, key));
    }

    void push(const Key& key, const Value& value)
    {
      insertNode(root_, key, value);
    }

    Value& drop(const Key& key)
    {
      detail::TreeNode< Key, Value >* nodePointer = findNode(root_, key);

      if (!nodePointer)
      {
        throw std::out_of_range("Key not found");
      }
      Value tempValue = nodePointer->data_.second;
      removeNode(nodePointer);
      return tempValue;
    }

    void insert(const Key& key, const Value& value)
    {
      try
      {
        if (root_)
        {
          insertNode(key, value, root_);
          ++size_;
        }
        else
        {
          root_ = new detail::TreeNode< Key, Value >(key, value);
          ++size_;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

  private:
    detail::TreeNode< Key, Value >* root_;
    Compare* cmp_;
    size_t size_;

    void removeNode(detail::TreeNode< Key, Value >* nodePointer)
    {
      if (nodePointer == nullptr)
      {
        return;
      }
      removeNode(nodePointer->left);
      removeNode(nodePointer->right);
      delete nodePointer;
    }

    detail::TreeNode< Key, Value >* findNode(detail::TreeNode< Key, Value >* nodePointer, const Key& key) const
    {
      if (!nodePointer)
      {
        return nullptr;
      }

      if (cmp_(key, nodePointer->data_.first))
      {
        return findNode(nodePointer->left_, key);
      }
      else if (cmp_(nodePointer->data_.first, key))
      {
        return findNode(nodePointer->right_, key);
      }
      else
      {
        return nodePointer;
      }
    }

    detail::TreeNode< Key, Value >* insertNode(detail::TreeNode< Key, Value >* nodePointer, const Key& key, const Value& value)
    {
      if (!nodePointer)
      {
        nodePointer = new detail::TreeNode< Key, Value >(key, value);
        size_++;
        return nodePointer;
      }

      if (cmp_(key, nodePointer->data_.first))
      {
        nodePointer->left_ = insertNode(nodePointer->left_, key, value);
      }
      else if (cmp_(nodePointer->data_.first, key))
      {
        nodePointer->right_ = insertNode(nodePointer->right_, key, value);
      }
      else
      {
        nodePointer->data_.second = value;
      }
      return balance(nodePointer);
    }

    long long int height(detail::TreeNode< Key, Value >* nodePointer)
    {
      if (nodePointer == nullptr)
      {
        return 0;
      }
      return nodePointer->height_;
    }

    long long int getBalanceFactor(detail::TreeNode< Key, Value >* nodePointer)
    {
      if (nodePointer == nullptr)
      {
        return 0;
      }
      return height(nodePointer->left_) - height(nodePointer->right_);
    }

    detail::TreeNode< Key, Value >* rightRotate(detail::TreeNode< Key, Value >* unbalancedNode)
    {
      detail::TreeNode< Key, Value >* leftChild = unbalancedNode->left_;
      detail::TreeNode< Key, Value >* leftRightChild = leftChild->right_;

      leftChild->right_ = unbalancedNode;
      unbalancedNode->left_ = leftRightChild;

      unbalancedNode->height_ = std::max(height(unbalancedNode->left_), height(unbalancedNode->right_)) + 1;
      leftChild->height_ = std::max(height(leftChild->left_), height(leftChild->right_)) + 1;

      return leftChild;
    }

    detail::TreeNode< Key, Value >* leftRotate(detail::TreeNode< Key, Value >* unbalancedNode)
    {
      detail::TreeNode< Key, Value >* rightChild = unbalancedNode->right_;
      detail::TreeNode< Key, Value >* rightLeftChild = rightChild->left_;

      rightChild->left_ = unbalancedNode;
      unbalancedNode->right_ = rightLeftChild;

      unbalancedNode->height_ = std::max(height(unbalancedNode->left_), height(unbalancedNode->right_)) + 1;
      rightChild->height_ = std::max(height(rightChild->left_), height(rightChild->right_)) + 1;

      return rightChild;
    }

    detail::TreeNode< Key, Value >* balance(detail::TreeNode< Key, Value >* nodePointer)
    {
      nodePointer->height_ = 1 + std::max(height(nodePointer->left_), height(nodePointer->right_));
      long long int balanceFactor = getBalanceFactor(nodePointer);

      if (balanceFactor > 1)
      {
        if (getBalanceFactor(nodePointer->left_) < 0)
        {
          nodePointer->left_ = leftRotate(nodePointer->left_);
        }
        return rightRotate(nodePointer);
      }

      if (balanceFactor < -1)
      {
        if (getBalanceFactor(nodePointer->right_) > 0)
        {
          nodePointer->right_ = rightRotate(nodePointer->right_);
        }
        return leftRotate(nodePointer);
      }
      return nodePointer;
    }
  };
}

#endif
