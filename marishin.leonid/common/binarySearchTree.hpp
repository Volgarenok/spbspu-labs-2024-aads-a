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
    using node_t = detail::TreeNode< Key, Value >;
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
        for (auto begin = rhs.cbegin(); begin != rhs.cend(); ++begin)
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
      size_(rhs.size_)
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

    size_t size() const noexcept
    {
      return size_;
    }

    ~BinarySearchTree()
    {
      clear();
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
          root_ = new node_t(key, val);
          ++size_;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    void insert_p(const Key& key, const Value& val, node_t* currNode)
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
            currNode->left = new node_t(key, val, currNode);
            getBalabce(currNode->left);
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
            currNode->right = new node_t(key, val, currNode);
            getBalabce(currNode->right);
          }
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    node_t search(const Key& key)
    {
      node_t* rhs = search_p(root_, key);
      return rhs;
    }

    ConstIteratorTree< Key, Value, Compare > cbegin() const noexcept
    {
      return ConstIteratorTree< Key, Value, Compare >(getMin(root_));
    }

    ConstIteratorTree< Key, Value, Compare > cend() const noexcept
    {
      return ConstIteratorTree< Key, Value, Compare >();
    }

    const Value& operator[](const Key& key) const
    {
      node_t* traverser = search(key);
      if (traverser)
      {
        return traverser->data.second;
      }
      else
      {
        insert(key, Value());
        node_t* result = search(key);
        return result->data.second;
      }
    }

    Value& operator[](const Key& key)
    {
      node_t* traverser = search(key);
      if (traverser)
      {
        return traverser->data.second;
      }
      else
      {
        insert(key, Value());
        node_t* result = search(key);
        return result->data.second;
      }
    }

    Value& at(const Key& key)
    {
      node_t* traverser = search(key);
      if (traverser)
      {
        return traverser->data.second;
      }
      throw std::out_of_range("No such element");
    }

    const Value& at(const Key& key) const
    {
      node_t* traverser = search(key);
      if (traverser)
      {
        return traverser->data.second;
      }
      throw std::out_of_range("No such element");
    }

    ConstIteratorTree< Key, Value, Compare > find(const Key& key) const
    {
      node_t* result = root_;
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

    void clear()
    {
      clear_p(root_);
      root_ = nullptr;
    }

  private:
    node_t* root_;
    size_t size_;
    Compare compare_;

    void clear_p(node_t* node)
    {
      if (node)
      {
        --size;
        clear_p(node->right);
        clear_p(node->left);
        delete node;
      }
    }

    void balance(node_t* node)
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

    void getBalance(node_t* node)
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

    node_t* getMin(node_t* node) const
    {
      node_t* result = node;
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

    node_t* rotateLeft(node_t* node)
    {
      node_t* newRoot = node->right;
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

    node_t* rotateRight(node_t* node)
    {
      node_t* newRoot = node->left;
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

    node_t* search_p(node_t* node, const Key& key)
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

    void insert_p(const Key& key, const Value& val, node_t* currNode)
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
            currNode->left = new node_t(key, val, currNode);
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
            currNode->right = new node_t(key, val, currNode);
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
