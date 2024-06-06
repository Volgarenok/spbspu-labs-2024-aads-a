#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstddef>
#include <algorithm>
#include <stdexcept>
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
          insert(it->first, it->second);
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

    ConstIteratorTree< Key, Value, Compare > cbegin() const noexcept
    {
      detail::TreeNode< Key, Value >* temp = root_;
      if (!temp)
      {
        return ConstIteratorTree< Key, Value, Compare > (nullptr);
      }
      while (temp->left_ != nullptr)
      {
        temp = temp->left_;
      }
      return ConstIteratorTree< Key, Value, Compare > (temp);
    }

    ConstIteratorTree< Key, Value, Compare > cend() const noexcept
    {
      return ConstIteratorTree< Key, Value, Compare > (nullptr);
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
        nodePointer = insertNode(root_, key, Value());
      }
      return nodePointer->data_.second;
    }

    void clear() noexcept
    {
      removeNode(root_, Key());
      root_ = nullptr;
      size_ = 0;
    }

    void swap(AVLTree& diff)
    {
      std::swap(root_, diff.root_);
      std::swap(cmp_, diff.cmp_);
      std::swap(size_, diff.size_);
    }

    ConstIteratorTree< Key, Value, Compare > find(const Key& key) const
    {
      return ConstIteratorTree< Key, Value, Compare > (findNode(root_, key));
    }

    Value& drop(const Key& key)
    {
      detail::TreeNode< Key, Value >* nodePointer = findNode(root_, key);

      if (!nodePointer)
      {
        throw std::out_of_range("Key not found");
      }
      Value tempValue = nodePointer->data_.second;
      root_ = removeNode(root_, key);
      --size_;
      return tempValue;
    }

    void insert(const Key& key, const Value& value)
    {
      try
      {
        if (root_)
        {
          insertNode(root_, key, value);
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
    Compare cmp_;
    size_t size_;

    detail::TreeNode< Key, Value >* removeNode(detail::TreeNode< Key, Value >* nodePointer, const Key& key)
    {
      if (nodePointer == nullptr)
      {
        return nodePointer;
      }

      if (cmp_(key, nodePointer->data_.first))
      {
        nodePointer->left_ = removeNode(nodePointer->left_, key);
      }
      else if (cmp_(nodePointer->data_.first, key))
      {
        nodePointer->right_ = removeNode(nodePointer->right_, key);
      }
      else
      {
        if ((nodePointer->left_ == nullptr) || (nodePointer->right_ == nullptr))
        {
          detail::TreeNode< Key, Value >* temp = nodePointer->left_ ? nodePointer->left_ : nodePointer->right_;

          if (temp == nullptr)
          {
            temp = nodePointer;
            nodePointer = nullptr;
          }
          else
          {
            *nodePointer = *temp;
          }

          delete temp;
        }
        else
        {
          detail::TreeNode< Key, Value >* temp = minValueNode(nodePointer->right_);
          nodePointer->data_ = temp->data_;
          nodePointer->right_ = removeNode(nodePointer->right_, temp->data_.first);
        }
      }

      if (nodePointer == nullptr)
      {
        return nodePointer;
      }

      nodePointer->height_ = 1 + std::max(height(nodePointer->left_), height(nodePointer->right_));

      return balance(nodePointer);
    }

    detail::TreeNode< Key, Value >* minValueNode(detail::TreeNode< Key, Value >* nodePointer)
    {
      detail::TreeNode< Key, Value >* current = nodePointer;
      while (current && current->left_ != nullptr)
      {
        current = current->left_;
      }
      return current;
    }

    /*void removeNode(detail::TreeNode< Key, Value >* nodePointer)
    {
      if (nodePointer == nullptr)
      {
        return;
      }
      removeNode(nodePointer->left_);
      removeNode(nodePointer->right_);
      delete nodePointer;
    }*/

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
        if (!root_)
        {
          root_ = nodePointer;
        }
        size_++;
        return nodePointer;
      }

      if (cmp_(key, nodePointer->data_.first))
      {
        nodePointer->left_ = insertNode(nodePointer->left_, key, value);
        nodePointer->left_->parent_ = nodePointer;
      }
      else if (cmp_(nodePointer->data_.first, key))
      {
        nodePointer->right_ = insertNode(nodePointer->right_, key, value);
        nodePointer->right_->parent_ = nodePointer;
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

      leftChild->parent_ = unbalancedNode->parent_;
      unbalancedNode->parent_ = leftChild;
      if (leftRightChild)
      {
        leftRightChild->parent_ = unbalancedNode;
      }

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

      rightChild->parent_ = unbalancedNode->parent_;
      unbalancedNode->parent_ = rightChild;
      if (rightLeftChild)
      {
        rightLeftChild->parent_ = unbalancedNode;
      }

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
