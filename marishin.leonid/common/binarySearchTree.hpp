#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <functional>
#include <stdexcept>
#include <treeNode.hpp>
#include <treeIterator.hpp>
#include <constTreeIterator.hpp>

namespace marishin
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BinarySearchTree
  {
  public:

    BinarySearchTree():
      root_(nullptr),
      size_(0),
      compare_(Compare())
    {}

    BinarySearchTree(const BinarySearchTree& rhs):
      root_(nullptr),
      size_(0),
      compare_(rhs.compare_)
    {
      try
      {
        ConstIteratorTree< Key, Value, Compare > begin = rhs.cbegin();
        ConstIteratorTree< Key, Value, Compare > end = rhs.cend();
        for (; begin != end; ++begin)
        {
          insert(begin->first, begin->second);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    BinarySearchTree(BinarySearchTree&& rhs):
      root_(rhs.root_),
      size_(rhs.size_),
      compare_(rhs.compare_)
    {
      rhs.root_ = nullptr;
      rhs.size_ = 0;
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs)
    {
      BinarySearchTree< Key, Value > temp(rhs);
      if (this != std::addressof(rhs))
      {
        swap(temp);
      }
      return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept
    {
      BinarySearchTree< Key, Value > temp(std::move(rhs));
      if (this != std::addressof(rhs))
      {
        swap(temp);
      }
      return *this;
    }

    void swap(BinarySearchTree< Key, Value, Compare >& rhs) noexcept
    {
      std::swap(root_, rhs.root_);
      std::swap(size_, rhs.size_);
      std::swap(compare_, rhs.compare_);
    }

    void insert(const Key& key, const Value& val)
    {
      try
      {
        if (root_)
        {
          insert_p(key, val, root_);
          ++size_;
        }
        else
        {
          root_ = new detail::TreeNode< Key, Value >(key, val);
          ++size_;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    void balance(detail::TreeNode< Key, Value >* node)
    {
      if (node->height < 0)
      {
        if (node->right->height > 0)
        {
          node->right = rotateRight(node->right);
        }
        node = rotateLeft(node);
      }
      else
      {
        if (node->left->height < 0)
        {
          node->left = rotateLeft(node->left);
        }
        node = rotateRight(node);
      }
    }

    void getBalance(detail::TreeNode< Key, Value >* node)
    {
      if (node->height > 1 || node->height < -1)
      {
        balance(node);
      }
      else
      {
        if (node->parent)
        {
          if (node->left)
          {
            ++node->parent->height;
          }
          else if (node->right)
          {
            --node->parent->height;
          }
          if (node->parent->height != 0)
          {
            getBalance(node->parent);
          }
        }
      }
    }

    detail::TreeNode< Key, Value >* search(const Key& key)
    {
      detail::TreeNode< Key, Value >* res = search_p(root_, key);
      return res;
    }

    ConstIteratorTree< Key, Value, Compare > cbegin() const noexcept
    {
      return ConstIteratorTree< Key, Value, Compare >(getMin(root_));
    }

    ConstIteratorTree< Key, Value, Compare > cend() const noexcept
    {
      return ConstIteratorTree< Key, Value, Compare >();
    }

    IteratorTree< Key, Value, Compare > begin() const noexcept
    {
      return IteratorTree< Key, Value, Compare >(getMin(root_));
    }

    IteratorTree< Key, Value, Compare > end() const noexcept
    {
      return IteratorTree< Key, Value, Compare >();
    }

    const Value& operator[](const Key& key) const
    {
      detail::TreeNode< Key, Value >* traverser = search(key);
      if (traverser)
      {
        return traverser->data.second;
      }
      else
      {
        insert(key, Value());
        detail::TreeNode< Key, Value >* result = search(key);
        return result->data.second;
      }
    }

    Value& operator[](const Key& key)
    {
      detail::TreeNode< Key, Value >* traverser = search(key);
      if (traverser)
      {
        return traverser->data.second;
      }
      else
      {
        insert(key, Value());
        detail::TreeNode< Key, Value >* result = search(key);
        return result->data.second;
      }
    }

    Value& at(const Key& key)
    {
      detail::TreeNode< Key, Value >* traverser = search(key);
      if (traverser)
      {
        return traverser->data.second;
      }
      throw std::out_of_range("No such element");
    }

    const Value& at(const Key& key) const
    {
      detail::TreeNode< Key, Value >* traverser = search(key);
      if (traverser)
      {
        return traverser->data.second;
      }
      throw std::out_of_range("No such element");
    }

    ConstIteratorTree< Key, Value, Compare > find(const Key& key) const
    {
      detail::TreeNode< Key, Value >* result = root_;
      while (result)
      {
        if (compare_(result->data.first, key))
        {
          result = result->right;
        }
        else if (compare_(key, result->data.first))
        {
          result = result->left;
        }
        else
        {
          break;
        }
      }
      return ConstIteratorTree< Key, Value, Compare >(result);
    }

    size_t size() const noexcept
    {
      return size_;
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    void clear()
    {
      clear_p(root_);
      root_ = nullptr;
    }

    ~BinarySearchTree()
    {
      clear();
    }

  private:
    detail::TreeNode< Key, Value >* root_;
    size_t size_;
    Compare compare_;

    void clear_p(detail::TreeNode< Key, Value >* node)
    {
      if (node)
      {
        --size;
        clear_p(node->right);
        clear_p(node->left);
        delete node;
      }
    }

    detail::TreeNode< Key, Value >* getMin(detail::TreeNode< Key, Value >* node) const
    {
      detail::TreeNode< Key, Value >* result = node;
      if (!result)
      {
        return nullptr;
      }
      while (result->left)
      {
        result = result->left;
      }
      return result;
    }

    detail::TreeNode< Key, Value >* rotateLeft(detail::TreeNode< Key, Value >* node)
    {
      detail::TreeNode< Key, Value >* newRoot = node->right;
      node->right = newRoot->left;
      if (newRoot->left)
      {
        newRoot->left->parent = node;
      }
      newRoot->left = node;
      node->parent = newRoot;
      node->height = node->height + 1 - std::min(newRoot->height, 0);
      newRoot->height = newRoot->height + 1 + std::max(node->height, 0);
      return newRoot;
    }

    detail::TreeNode< Key, Value >* rotateRight(detail::TreeNode< Key, Value >* node)
    {
      detail::TreeNode< Key, Value >* newRoot = node->left;
      node->left = newRoot->right;
      if (newRoot->right)
      {
        newRoot->right->parent = node;
      }
      newRoot->right = node;
      node->parent = newRoot;
      node->height = node->height - 1 - std::max(0, newRoot->height);
      newRoot->height = newRoot->height - 1 + std::min(0, node->height);
      return newRoot;
    }

    detail::TreeNode< Key, Value >* search_p(detail::TreeNode< Key, Value >* node, const Key& key)
    {
      if (!node)
      {
        return nullptr;
      }
      else if (compare_(key, node->data.first))
      {
        return search_p(node->left, key);
      }
      else if (compare_(node->data.first, key))
      {
        return search_p(node->right, key);
      }
      else
      {
        return node;
      }
    }

    void insert_p(const Key& key, const Value& val, detail::TreeNode< Key, Value >* currNode)
    {
      try
      {
        if (compare_(key, currNode->data.first))
        {
          if (currNode->left)
          {
            insert_p(key, val, currNode->left);
          }
          else
          {
            currNode->left = new detail::TreeNode< Key, Value >(key, val, currNode);
            getBalance(currNode->left);
          }
        }
        else
        {
          if (currNode->right)
          {
            insert_p(key, val, currNode->right);
          }
          else
          {
            currNode->right = new detail::TreeNode< Key, Value >(key, val, currNode);
            getBalance(currNode->right);
          }
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
  };
}

#endif
