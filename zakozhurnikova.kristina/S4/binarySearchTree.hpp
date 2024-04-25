#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include "comparator.hpp"
#include "constIterator.hpp"
#include "treeNode.hpp"

namespace zakozhurnikova
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  struct BinarySearchTree
  {
    using node = detail::TreeNode< Key, Value >;
    BinarySearchTree():
      root_(nullptr),
      size_(0),
      compare_(Compare())
    {}

    BinarySearchTree(BinarySearchTree&& rhs):
      root_(rhs.root_),
      size_(rhs.size_),
      compare_(rhs.compare_)
    {
      rhs.root_ = nullptr;
      rhs.size_ = 0;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs)
    {
      if (this != std::addressof(rhs))
      {
        std::swap(root_, rhs.root_);
        std::swap(size_, rhs.size_);
        std::swap(compare_, rhs.compare_);
      }
      return *this;
    }

    ~BinarySearchTree()
    {
      clear();
    }

    int length() const noexcept
    {
      return this->size_;
    }

    void swap(BinarySearchTree< Key, Value, Compare >& other)
    {
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(compare_, other.compare_);
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    void push(Key key, Value val)
    {
      if (root_)
      {
        put(key, std::move(val), root_);
      }
      else
      {
        root_ = new node(key, std::move(val));
      }
      size_ = size_ + 1;
    }

    void put(Key key, Value val, node* currentNode)
    {
      if (compare_(key, currentNode->data.first))
      {
        if (currentNode->hasLeftChild())
        {
          put(key, std::move(val), currentNode->leftChild);
        }
        else
        {
          currentNode->leftChild = new node(key, std::move(val), currentNode);
          updateBalance(currentNode->leftChild);
        }
      }
      else
      {
        if (currentNode->hasRightChild())
        {
          put(key, std::move(val), currentNode->rightChild);
        }
        else
        {
          currentNode->rightChild = new node(key, std::move(val), currentNode);
          updateBalance(currentNode->rightChild);
        }
      }
    }

    void rebalance(node* node)
    {
      if (node->balanceFactor < 0)
      {
        if (node->rightChild->balanceFactor > 0)
        {
          rotateRight(node->rightChild);
          rotateLeft(node);
        }
        else
        {
          rotateLeft(node);
        }
      }
      else
      {
        if (node->leftChild->balanceFactor < 0)
        {
          rotateLeft(node->leftChild);
          rotateRight(node);
        }
        else
        {
          rotateRight(node);
        }
      }
    }

    void updateBalance(node* node)
    {
      if (node->balanceFactor > 1 || node->balanceFactor < -1)
      {
        rebalance(node);
        return;
      }
      if (node->parent != nullptr)
      {
        if (node->isLeftChild())
        {
          node->parent->balanceFactor += 1;
        }
        else if (node->isRightChild())
        {
          node->parent->balanceFactor -= 1;
        }
        if (node->parent->balanceFactor != 0)
        {
          updateBalance(node->parent);
        }
      }
    }

    void rotateLeft(node* rotRoot)
    {
      node* newRoot = rotRoot->rightChild;
      rotRoot->rightChild = newRoot->leftChild;
      if (newRoot->leftChild != nullptr)
      {
        newRoot->leftChild->parent = rotRoot;
      }
      newRoot->parent = rotRoot->parent;
      if (rotRoot->isRoot())
      {
        root_ = newRoot;
      }
      else
      {
        if (rotRoot->isLeftChild())
        {
          rotRoot->parent->leftChild = newRoot;
        }
        else
        {
          rotRoot->parent->rightChild = newRoot;
        }
      }
      newRoot->leftChild = rotRoot;
      rotRoot->parent = newRoot;
      rotRoot->balanceFactor = rotRoot->balanceFactor + 1 - std::min(newRoot->balanceFactor, 0);
      newRoot->balanceFactor = newRoot->balanceFactor + 1 + std::max(rotRoot->balanceFactor, 0);
    }

    void rotateRight(node* rotRoot)
    {
      node* newRoot = rotRoot->leftChild;
      rotRoot->leftChild = newRoot->rightChild;
      if (newRoot->rightChild != nullptr)
      {
        newRoot->rightChild->parent = rotRoot;
      }
      newRoot->parent = rotRoot->parent;
      if (rotRoot->isRoot())
      {
        root_ = newRoot;
      }
      else
      {
        if (rotRoot->isLeftChild())
        {
          rotRoot->parent->leftChild = newRoot;
        }
        else
        {
          rotRoot->parent->rightChild = newRoot;
        }
      }
      newRoot->rightChild = rotRoot;
      rotRoot->parent = newRoot;
      rotRoot->balanceFactor = rotRoot->balanceFactor - 1 - std::max(0, newRoot->balanceFactor);
      newRoot->balanceFactor = newRoot->balanceFactor - 1 + std::min(0, rotRoot->balanceFactor);
    }

    Value& get(Key key)
    {
      node* res = get(key, root_);
      if (res)
      {
        return res->data.second;
      }
      else
      {
        return res->data.second;
      }
    }

    node* get(Key key, node* currentNode)
    {
      if (!currentNode)
      {
        return nullptr;
      }
      else if (currentNode->data.first == key)
      {
        return currentNode;
      }
      else if (compare_(key, currentNode->data.first))
      {
        return get(key, currentNode->leftChild);
      }
      else
      {
        return get(key, currentNode->rightChild);
      }
    }

    void del(Key key)
    {
      if (size_ > 1)
      {
        node* nodeToRemove = get(key, root_);
        if (nodeToRemove)
        {
          remove(nodeToRemove);
          size_ = size_ - 1;
        }
        else
        {
          std::cerr << "Error, key not in tree" << '\n';
        }
      }
      else if (size_ == 1 && root_->data.first == key)
      {
        root_ = nullptr;
        size_ = size_ - 1;
      }
      else
      {
        std::cerr << "Error, key not in tree" << '\n';
      }
    }

    void updateRemoveBalance(node* balanceParent, const int& oldBal)
    {
      if (balanceParent->balanceFactor == 0)
      {
        if (!balanceParent->isRoot())
        {
          int bal = balanceParent->parent->balanceFactor;
          if (balanceParent->isLeftChild())
          {
            --balanceParent->parent->balanceFactor;
          }
          else
          {
            ++balanceParent->parent->balanceFactor;
          }
          updateRemoveBalance(balanceParent->parent, bal);
        }
      }
      else if (1 < balanceParent->balanceFactor || -1 > balanceParent->balanceFactor)
      {
        if (!balanceParent->isRoot())
        {
          node* grandParent = balanceParent->parent;
          bool leftChild = balanceParent->isLeftChild();
          rebalance(balanceParent);
          int newBal = 0;
          if (leftChild)
          {
            newBal = grandParent->leftChild->balanceFactor;
          }
          else
          {
            newBal = grandParent->rightChild->balanceFactor;
          }
          newBal = std::abs(newBal) - std::abs(oldBal);
          if (std::abs(newBal) - std::abs(oldBal) != 0)
          {
            int balGrand = grandParent->balanceFactor;
            if (leftChild)
            {
              --grandParent->balanceFactor;
            }
            else
            {
              ++grandParent->balanceFactor;
            }
            updateRemoveBalance(grandParent, balGrand);
          }
        }
        else
        {
          rebalance(balanceParent);
        }
      }
      return;
    }

    void remove(node* currentNode)
    {
      if (currentNode->isLeaf())
      {
        int oldBal = currentNode->parent->balanceFactor;
        if (currentNode->isLeftChild())
        {
          currentNode->parent->leftChild = nullptr;
          --currentNode->parent->balanceFactor;
        }
        else
        {
          currentNode->parent->rightChild = nullptr;
          ++currentNode->parent->balanceFactor;
        }
        node* balanceParent = currentNode->parent;
        delete currentNode;
        updateRemoveBalance(balanceParent, oldBal);
      }
      else if (currentNode->hasBothChildren())
      {
        node* succ = getLowest(currentNode->rightChild);
        node* parentRemove = succ->parent;
        int oldBal = parentRemove->balanceFactor;
        if (parentRemove->isLeftChild())
        {
          --parentRemove->balanceFactor;
        }
        else
        {
          ++parentRemove->balanceFactor;
        }
        succ->spliceOut();
        currentNode->data.first = succ->data.first;
        currentNode->data.second = succ->data.second;
        delete succ;
        updateRemoveBalance(parentRemove, oldBal);
      }
      else
      {
        if (currentNode->hasLeftChild())
        {
          if (currentNode->isLeftChild())
          {
            currentNode->leftChild->parent = currentNode->parent;
            currentNode->parent->leftChild = currentNode->leftChild;
          }
          else if (currentNode->isRightChild())
          {
            currentNode->leftChild->parent = currentNode->parent;
            currentNode->parent->rightChild = currentNode->leftChild;
          }

          int oldBal = currentNode->parent->balanceFactor;
          --currentNode->parent->balanceFactor;
          updateRemoveBalance(currentNode->parent, oldBal);

          if (currentNode->isRoot())
          {
            root_ = currentNode->leftChild;
            root_->parent = nullptr;
          }
        }
        else
        {
          if (currentNode->isLeftChild())
          {
            currentNode->rightChild->parent = currentNode->parent;
            currentNode->parent->leftChild = currentNode->rightChild;
          }
          else if (currentNode->isRightChild())
          {
            currentNode->rightChild->parent = currentNode->parent;
            currentNode->parent->rightChild = currentNode->rightChild;
          }

          int oldBal = currentNode->parent->balanceFactor;
          ++currentNode->parent->balanceFactor;
          updateRemoveBalance(currentNode->parent, oldBal);

          if (currentNode->isRoot())
          {
            root_ = currentNode->rightChild;
            root_->parent = nullptr;
          }
        delete currentNode;
        }
      }
    }

      node* getLowest(node * prev) const
      {
        node* lowest = prev;
        if (!lowest)
        {
          return nullptr;
        }
        while (lowest->leftChild != nullptr)
        {
          lowest = lowest->leftChild;
        }

        return lowest;
      }

      node* getNext(node * prev) const
      {
        node* cur = prev;
        while (cur->rightChild == nullptr || cur->data.first < prev->data.first)
        {
          if (cur->parent == nullptr)
          {
            return nullptr;
          }
          cur = cur->parent;
          if (cur->data.first > prev->data.first)
          {
            return cur;
          }
        }
        cur = cur->rightChild;
        cur = getLowest(cur);
        return cur;
      }

      ConstIterator< Key, Value, Compare > cbegin() noexcept
      {
        return ConstIterator< Key, Value, Compare >(getLowest(root_));
      }
      ConstIterator< Key, Value, Compare > cend() noexcept
      {
        return ConstIterator< Key, Value, Compare >();
      }

    private:
      node* root_;
      size_t size_;
      Compare compare_;

      void clear()
      {
        clear(root_);
      }
      void clear(node * node)
      {
        if (node != nullptr)
        {
          clear(node->leftChild);
          clear(node->rightChild);
          delete node;
        }
        root_ = nullptr;
      }
    };
  }

#endif
