#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstddef>
#include <algorithm>
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
      Value tempValue = nodePointer->data.second;
      removeNode(nodePointer);
      return tempValue;
    }

  private:
    detail::TreeNode< Key, Value >* root_;
    Compare* cmp_;
    size_t size_;

    void removeNode(detail::TreeNode< Key, Value >* node)
    {
      if (node == nullptr)
      {
        return;
      }
      removeNode(node->left);
      removeNode(node->right);
      delete node;
    }

    detail::TreeNode< Key, Value >* findNode(detail::TreeNode< Key, Value >* nodePointer, const Key& key) const
    {
      if (!nodePointer)
      {
        return nullptr;
      }

      if (Compare()(key, nodePointer->data.first))
      {
        return findNode(nodePointer->left, key);
      }
      else if (Compare()(nodePointer->data.first, key))
      {
        return findNode(nodePointer->right, key);
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
        return nodePointer;
      }

      if (key < nodePointer->data_.first)
      {
        return insertNode(nodePointer->left, key, value);
      }
      else if (key > nodePointer->data_.first)
      {
        return insertNode(nodePointer->right, key, value);
      }
      else
      {
        nodePointer->data.second = value;
        return nodePointer;
      }
    }
  };
}

#endif
