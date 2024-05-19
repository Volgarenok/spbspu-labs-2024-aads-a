#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <stdexcept>

namespace marishin
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  struct BinarySearchTree
  {
    using node_t = detail::TreeNode< Key, Value >;
    BinarySearchTree():
      root_(nullptr),
      size_(0)
    {}

    BinarySearchTree(const BinarySearchTree& rhs):
      root_(nullptr),
      size_(0)
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
      Tree< Key, Value > temp(std::move(rhs));
      if (this != std::addressof(rhs))
      {
        swap(temp);
      }
      return *this;
    }

    size_t size() const noexcept
    {
      return this->size_;
    }

    ~BinarySearchTree()
    {
      clear();
    }

    void swap(BinarySearchTree< Key, Value, Compare >& rhs) noexcept
    {
      std::swap(root_, rhs.root_);
      std::swap(size_, rhs.size_);
    }

    node_t* insert(const Key& key, const Value& val)
    {
      node_t* node;
      if (root_)
      {
        node = insert_p(key, val, root_);
        ++size_;
      }
      else
      {
        root_ = new node_t(key, val);
        node = root_;
        ++size_;
      }
      return node;
    }

    node_t* insert_p(const Key& key, const Value& val, node_t* currNode)
    {
      node_t* node;
      if (compare()(key, currNode->data.first))
      {
        if (currNode->hasLeft())
        {
          node = insert_p(key, val, currNode->left);
        }
        else
        {
          currNode->left = new node_t(key, val, currNode);
          getBalabce(currNode->left);
          return currNode->left;
        }
      }
      else
      {
        if (currNode->hasRight())
        {
          node = insert_p(key, val, currNode->right);
        }
        else
        {
          currNode->right = new node_t(key, val, currNode);
          getBalabce(currNode->right);
          return currNode->right;
        }
      }
      return node;
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    void del(const Key& key)
    {
      if (size_ == 1 && root_->data.first == key)
      {
        --size_;
        root_ = nullptr;
      }
      else if (size_ > 1)
      {
        node_t* nodeRemove = get(key, root_);
        if (nodeRemove)
        {
          remove(nodeRemove);
          --size_;
        }
        else
        {
          throw std::out_of_range("Error\n");
        }
      }
      else
      {
        throw std::out_of_range("Error\n");
      }
    }

    const_iterator_tree< Key, Value, Compare > cbegin() const noexcept
    {
      return const_iterator_tree< Key, Value, Comparee >(getMin(root_));
    }

    const_iterator_tree< Key, Value, Compare > cend() const noexcept
    {
      return const_iterator_tree< Key, Value, Comparee >();
    }

    const Value& operator[](const Key& key) const
    {
      node_t* traverser = get(key, root_);
      return traverser->data.second;
    }

    Value& operator[](const Key& key)
    {
      node_t* traverser = get(key, root_);
      if (traverser)
      {
        return traverser->data.second;
      }
      else
      {
        traverser = insert(key, Value());
      }
    }

    Value& at(const Key& key)
    {
      node_t* traverser = get(key, root_);
      if (traverser)
      {
        return traverser->data.second;
      }
      throw std::out_of_range("No such element");
    }

    const Value& at(const Key& key) const
    {
      node_t* traverser = get(key, root_);
      if (traverser)
      {
        return traverser->data.second;
      }
      throw std::out_of_range("No such element");
    }

    const_iterator< Key, Value > find(const Key& key) const
    {
      node_t* result = root_;
      while (result)
      {
        if (compare()(result->data.first, key))
        {
          result = result->right;
        }
        else if (compare()(key, result->data.first))
        {
          result = result->left;
        }
        else
        {
          break;
        }
      }
      return const_iterator_tree< Key, Value >(result);
    }

  private:
    node_t* root_;
    size_t size_;

    void clear()
    {
      clear(root_);
      root_ = nullptr;
    }

    void clear(node_t* node)
    {
      if (node)
      {
        clear(node->right);
        clear (node->left);
        delete node;
      }
    }

    Value& get(const Key& key) const
    {
      node_t* result = get(key, root_);
      return result->data.second;
    }

    node_t* get(const Key& key, node_t* currNode) const
    {
      if (!currNode)
      {
        return nullptr;
      }
      else if (currNode->data.first == key)
      {
        return currNode;
      }
      else if (compare()(key, currNode->data.first))
      {
        return get(key, currNode->left);
      }
      else
      {
        return get(key, currentNode->right);
      }
    }

    void balance(node_t* node)
    {
      if (node->height < 0)
      {
        if (node->right->height > 0)
        {
          node->right->rotateRight(&root_);
        }
        node->rotateLeft(&root_);
      }
      else
      {
        if (node->left->height < 0)
        {
          node->left->rotateLeft(&root_);
        }
        node->rotateRight(&root_);
      }
    }

    void getBalance(node_t* node)
    {
      if (node->height > 1 || node->height < -1)
      {
        balance(node);
        return;
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

    void updateBalance(node_t* balanceParent, int oldBal)
    {
      if (balanceParent->height == 0)
      {
        if (!balanceParent->isRoot())
        {
          int bal = balanceParent->parent->height;
          if (balanceParent->isLeft())
          {
            --balanceParent->parent->height;
          }
          else
          {
            ++balanceParent->parent->height;
          }
          updateBalance(balanceParent->parent, bal);
        }
      }
      else if (1 < balanceParent->height || -1 > balanceParent->height)
      {
        if (!balanceParent->isRoot())
        {
          node_t* grandParent = balanceParent->parent;
          bool left = balanceParent->isLeft();
          balance(balanceParent);
          int newBal = 0;
          if (left)
          {
            newBal = grandParent->left->height;
          }
          else
          {
            newBal = grandParent->right->height;
          }
          newBal = std::abs(newBal) - std::abs(oldBal);
          if (std::abs(newBal) - std::abs(oldBal) != 0)
          {
            int balGrand = grandParent->height;
            if (left)
            {
              --grandParent->height;
            }
            else
            {
              ++grandParent->height;
            }
            updateBalance(grandParent, balGrand);
          }
        }
        else
        {
          balance(balanceParent);
        }
      }
      return;
    }

    void remove(node_t* currNode)
    {
      if (currNode->isLeaf())
      {
        int oldBal = currNode->parent->height;
        if (currNode->isLeft())
        {
          currNode->parent->left = nullptr;
          --currNode->parent->height;
        }
        else
        {
          currNode->parent->right = nullptr;
          ++currNode->parent->height;
        }
        node_t* balanceParent = currNode->parent;
        delete currNode;
        updateBalance(balanceParent, oldBal);
      }
      else if (currNode->hasBoth())
      {
        node_t* res = getMin(currNode->right);
        currNode->data.first = res->data.first;
        currNode->data.second = res->data.second;
        remove(res);
      }
      else
      {
        if (currNode->hasLeft())
        {
          int oldBal = currNode->parent->height;
          if (currNode->isLeft())
          {
            currNode->left->parent = currNode->parent;
            currNode->parent->left = currNode->left;
            --currNode->parent->height;
          }
          else if (currNode->isRight())
          {
            currNode->left->parent = currNode->parent;
            currNode->parent->right = currNode->left;
            ++currNode->parent->height;
          }
          updateBalance(currNode->parent, oldBal);

          if (currNode->isRoot())
          {
            root_ = currNode->left;
            root_->parent = nullptr;
          }
        }
        else
        {
          int oldBal = currNode->parent->height;
          if (currNode->isLeft())
          {
            currNode->right->parent = currNode->parent;
            currNode->parent->left = currNode->right;
            --currNode->parent->height;
          }
          else if (currNode->isRight())
          {
            currNode->right->parent = currNode->parent;
            currNode->parent->right = currNode->right;
            ++currNode->parent->height;
          }
          updateBalance(currNode->parent, oldBal);

          if (currNode->isRoot())
          {
            root_ = currNode->right;
            root_->parent = nullptr;
          }
        }
        delete currNode;
      }
    }
  };
}

#endif
