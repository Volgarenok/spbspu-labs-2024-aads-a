#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <treeNode.hpp>
#include <constIteratorTree.hpp>

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

    BinarySearchTree(const BinarySearchTree& rhs):
      root_(nullptr),
      size_(0),
      compare_(rhs.compare_)
    {
      for (auto it = rhs.cbegin(); it != rhs.cend(); ++it)
      {
        push(it->first, it->second);
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
      if (this != std::addressof(rhs))
      {
        BinarySearchTree< Key, Value > temp(rhs);
        swap(temp);
      }
      return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs)
    {
      if (this != std::addressof(rhs))
      {
        swap(rhs);
      }
      return *this;
    }

    ~BinarySearchTree()
    {
      clear();
    }

    int size() const noexcept
    {
      return this->size_;
    }

    void swap(BinarySearchTree< Key, Value, Compare >& other) noexcept
    {
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(compare_, other.compare_);
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    void push(const Key& key, const Value& val)
    {
      if (root_)
      {
        put(key, val, root_);
      }
      else
      {
        root_ = new node(key, val);
      }
      size_ = size_ + 1;
    }

    void put(const Key& key,const Value& val, node* currentNode)
    {
      if (compare_(key, currentNode->data.first))
      {
        if (currentNode->hasLeftChild())
        {
          put(key, val, currentNode->leftChild);
        }
        else
        {
          currentNode->leftChild = new node(key, val, currentNode);
          updateBalance(currentNode->leftChild);
        }
      }
      else
      {
        if (currentNode->hasRightChild())
        {
          put(key, val, currentNode->rightChild);
        }
        else
        {
          currentNode->rightChild = new node(key, val, currentNode);
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

    Value& get(const Key& key)
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

    node* get(const Key& key, node* currentNode)
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

    void del(const Key& key)
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

    void updateRemoveBalance(node* balanceParent, int oldBal)
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
        currentNode->data.first = succ->data.first;
        currentNode->data.second = succ->data.second;
        remove(succ);
      }
      else
      {
        if (currentNode->hasLeftChild())
        {
          int oldBal = currentNode->parent->balanceFactor;
          if (currentNode->isLeftChild())
          {
            currentNode->leftChild->parent = currentNode->parent;
            currentNode->parent->leftChild = currentNode->leftChild;
            --currentNode->parent->balanceFactor;
          }
          else if (currentNode->isRightChild())
          {
            currentNode->leftChild->parent = currentNode->parent;
            currentNode->parent->rightChild = currentNode->leftChild;
            ++currentNode->parent->balanceFactor;
          }
          updateRemoveBalance(currentNode->parent, oldBal);

          if (currentNode->isRoot())
          {
            root_ = currentNode->leftChild;
            root_->parent = nullptr;
          }
        }
        else
        {
          int oldBal = currentNode->parent->balanceFactor;
          if (currentNode->isLeftChild())
          {
            currentNode->rightChild->parent = currentNode->parent;
            currentNode->parent->leftChild = currentNode->rightChild;
            --currentNode->parent->balanceFactor;
          }
          else if (currentNode->isRightChild())
          {
            currentNode->rightChild->parent = currentNode->parent;
            currentNode->parent->rightChild = currentNode->rightChild;
            ++currentNode->parent->balanceFactor;
          }
          updateRemoveBalance(currentNode->parent, oldBal);

          if (currentNode->isRoot())
          {
            root_ = currentNode->rightChild;
            root_->parent = nullptr;
          }
        }
        delete currentNode;
      }
    }

    node* getLowest(node* prev) const
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

    ConstIteratorTree< Key, Value, Compare > cbegin() const noexcept
    {
      return ConstIteratorTree< Key, Value, Compare >(getLowest(root_));
    }
    ConstIteratorTree< Key, Value, Compare > cend() const noexcept
    {
      return ConstIteratorTree< Key, Value, Compare >();
    }

    Value& operator[](const Key& key)
    {
      node* traverser = get(key, root_);
      if (traverser)
      {
        return traverser->data.second;
      }
      else
      {
        push(key, Value());
        return get(key, root_)->data.second;
      }
    }

    Value& at(const Key& key)
    {
      node* traverser = get(key, root_);
      if (traverser)
      {
        return traverser->data.second;
      }
      throw std::out_of_range("No such element");
    }

    ConstIteratorTree< Key, Value > find(const Key& key) const
    {
      node* wanted = root_;
      while (wanted)
      {
        if (wanted->data.first == key)
        {
          break;
        }
        else if (compare_(wanted->data.first, key))
        {
          wanted = wanted->rightChild;
        }
        else
        {
          wanted = wanted->leftChild;
        }
      }
      return ConstIteratorTree< Key, Value >(wanted);
    }

  private:
    node* root_;
    size_t size_;
    Compare compare_;

    void clear()
    {
      clear(root_);
      root_ = nullptr;
    }
    void clear(node* node)
    {
      if (node != nullptr)
      {
        clear(node->leftChild);
        clear(node->rightChild);
        delete node;
      }
    }
  };
}

#endif
