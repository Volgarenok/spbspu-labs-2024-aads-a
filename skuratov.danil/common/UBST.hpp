#ifndef UBST_HPP
#define UBST_HPP

#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include "treeNode.hpp"
#include "iteratorTree.hpp"
#include "queue.hpp"
#include "stack.hpp"

namespace skuratov
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class UBST
  {
  public:
    UBST():
      root_(nullptr),
      cmp_(Compare()),
      size_(0)
    {}

    ~UBST()
    {
      clear();
    }

    UBST(const UBST& diff):
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

    UBST& operator=(const UBST& diff)
    {
      if (this != std::addressof(diff))
      {
        UBST tempNode(diff);
        swap(tempNode);
      }
      return *this;
    }

    UBST(UBST&& diff) noexcept:
      root_(diff.root_),
      cmp_(diff.cmp_),
      size_(diff.size_)
    {
      diff.root_ = nullptr;
      diff.size_ = 0;
    }

    UBST& operator=(UBST&& diff) noexcept
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
        return ConstIteratorTree< Key, Value, Compare >(nullptr);
      }
      while (temp->left_ != nullptr)
      {
        temp = temp->left_;
      }
      return ConstIteratorTree< Key, Value, Compare >(temp);
    }

    ConstIteratorTree< Key, Value, Compare > cend() const noexcept
    {
      return ConstIteratorTree< Key, Value, Compare >(nullptr);
    }

    IteratorTree< Key, Value, Compare > begin() noexcept
    {
      detail::TreeNode< Key, Value >* temp = root_;
      if (!temp)
      {
        return IteratorTree< Key, Value, Compare >(nullptr);
      }
      while (temp->left_ != nullptr)
      {
        temp = temp->left_;
      }
      return IteratorTree< Key, Value, Compare >(temp);
    }

    IteratorTree< Key, Value, Compare > end() noexcept
    {
      return IteratorTree< Key, Value, Compare >(nullptr);
    }

    size_t size() const noexcept
    {
      return size_;
    }

    size_t count(const Key& key) const
    {
      return find(key) != cend();
    }

    bool empty() const noexcept
    {
      return (size_ == 0);
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
        insert(key, Value());
        nodePointer = findNode(root_, key);
      }
      return nodePointer->data_.second;
    }

    const Value& operator[](const Key& key) const
    {
      detail::TreeNode< Key, Value >* nodePointer = findNode(root_, key);

      if (nodePointer == nullptr)
      {
        insert(key, Value());
        nodePointer = findNode(root_, key);
      }
      return nodePointer->data_.second;
    }

    void clear() noexcept
    {
      removeNode(root_);
      root_ = nullptr;
      size_ = 0;
    }

    void swap(UBST& diff)
    {
      std::swap(root_, diff.root_);
      std::swap(cmp_, diff.cmp_);
      std::swap(size_, diff.size_);
    }

    ConstIteratorTree< Key, Value, Compare > find(const Key& key) const
    {
      return ConstIteratorTree< Key, Value, Compare >(findNode(root_, key));
    }

    void insert(const Key& key, const Value& value)
    {
      try
      {
        if (!findNode(root_, key))
        {
          root_ = insertNode(root_, key, value);
          ++size_;
        }
        else
        {
          detail::TreeNode< Key, Value >* nodePointer = findNode(root_, key);
          nodePointer->data_.second = value;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    void erase(const Key& key)
    {
      root_ = eraseNode(root_, key);
    }

    std::pair< ConstIteratorTree< Key, Value, Compare >, ConstIteratorTree< Key, Value, Compare > > equalRange(const Key& key) const
    {
      auto isLow = lower_bound(key);
      auto isHigh = upper_bound(key);
      return std::make_pair(isLow, isHigh);
    }

    std::pair< IteratorTree< Key, Value, Compare >, IteratorTree< Key, Value, Compare > > equalRange(const Key& key)
    {
      auto isLow = lower_bound(key);
      auto isHigh = upper_bound(key);
      return std::make_pair(isLow, isHigh);
    }

    template< typename F >
    F traverseLnr(F f) const
    {
      Stack< detail::TreeNode< Key, Value >* > stack;
      detail::TreeNode< Key, Value>* current = root_;

      while (current || !stack.empty())
      {
        while (current)
        {
          stack.push(current);
          current = current->left_;
        }
        current = stack.top();
        stack.drop();
        f(current->data_);
        current = current->right_;
      }
      return f;
    }

    template< typename F >
    F traverseRnl(F f) const
    {
      Stack< detail::TreeNode< Key, Value>* > stack;
      detail::TreeNode< Key, Value>* current = root_;

      while (current || !stack.empty())
      {
        while (current)
        {
          stack.push(current);
          current = current->right_;
        }

        current = stack.top();
        stack.drop();
        f(current->data_);
        current = current->left_;
      }
      return f;
    }

    template< typename F >
    F traverseBreadth(F f) const
    {
      Queue< detail::TreeNode< Key, Value >* > queue;
      queue.push(root_);

      while (!queue.empty())
      {
        detail::TreeNode< Key, Value >* current = queue.front();
        queue.drop();
        f(current->data_);

        if (current->left_)
        {
          queue.push(current->left_);
        }
        if (current->right_)
        {
          queue.push(current->right_);
        }
      }
      return f;
    }

  private:
    detail::TreeNode< Key, Value >* root_;
    Compare cmp_;
    size_t size_;

    void removeNode(detail::TreeNode< Key, Value >* nodePointer)
    {
      if (nodePointer == nullptr)
      {
        return;
      }
      removeNode(nodePointer->left_);
      removeNode(nodePointer->right_);
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

    detail::TreeNode<Key, Value>* insertNode(detail::TreeNode< Key, Value >* nodePointer, const Key& key, const Value& value)
    {
      if (!nodePointer)
      {
        return new detail::TreeNode<Key, Value>(key, value);
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
      return nodePointer;
    }

    detail::TreeNode< Key, Value >* eraseNode(detail::TreeNode< Key, Value >* nodePointer, const Key& key)
    {
      if (!nodePointer)
      {
        return nullptr;
      }

      if (cmp_(key, nodePointer->data_.first))
      {
        nodePointer->left_ = eraseNode(nodePointer->left_, key);
      }
      else if (cmp_(nodePointer->data_.first, key))
      {
        nodePointer->right_ = eraseNode(nodePointer->right_, key);
      }
      else
      {
        if (!nodePointer->left_)
        {
          detail::TreeNode< Key, Value >* temp = nodePointer->right_;
          delete nodePointer;
          --size_;
          return temp;
        }
        else if (!nodePointer->right_)
        {
          detail::TreeNode< Key, Value >* temp = nodePointer->left_;
          delete nodePointer;
          --size_;
          return temp;
        }

        detail::TreeNode< Key, Value >* temp = nodePointer->right_;
        while (temp->left_ != nullptr)
        {
          temp = temp->left_;
        }

        nodePointer->data_ = temp->data_;
        nodePointer->right_ = eraseNode(nodePointer->right_, temp->data_.first);
      }
      return nodePointer;
    }
  };
}

#endif
