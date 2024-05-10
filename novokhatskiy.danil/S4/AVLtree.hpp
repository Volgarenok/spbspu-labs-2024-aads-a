#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "AVLtreeNode.hpp"
#include "constIteratorTree.hpp"
#include "IteratorTree.hpp"

namespace novokhatskiy
{
  template <class Key, class Value, class Compare = std::less<Key>>
  class Tree
  {
  public:
    using node_t = detail::NodeTree<Key, Value>;
    using v_type = std::pair<Key, Value>;
    using constIter = ConstIteratorTree< Key, Value, Compare >;
    using iter = IteratorTree< Key, Value, Compare >;
    /*int getBalanceFactor(node_t* node)
    {
      if (node == nullptr)
      {
        return -1;
      }
      else
      {
        return;
      }
    }*/

    Tree():
      root_(nullptr),
      size_(0),
      cmp_()
    {}

    Tree(Tree&& other): 
      root_(other.root_),
      size_(other.size_),
      cmp_(std::move(other.cmp_))
    {
      other.root_ = nullptr;
      other.size_ = 0;
    }

    Tree& operator=(const Tree& other)
    {
      if (this != std::addressof(other))
      {
        Tree<Key, Value> tmp(other);
        swap(tmp);
      }
      return *this;
    }

    Tree& operator=(Tree&& other)
    {
      if (this != std::addressof(other))
      {
        swap(other);
      }
      return *this;
    }

    node_t* find(node_t* node, const Key& key)
    {
      node_t* root = (node->height < 0) ? node->left : node;
      while (root)
      {
        if (key == root->value.first)
        {
          return root;
        }
        if (cmp_(key, root->value.first))
        {
          if (!root->left)
          {
            return root;
          }
          root = root->left;
        }
        else
        {
          if (!root->right)
          {
            return root;
          }
          root = root->right;
        }
      }
      return nullptr;
    }

    Value& at(const Key& key)
    {
      node_t* curr = find(root_->left, key);
      if (curr && curr->value.first == key)
      {
        return curr->value.second;
      }
      throw std::out_of_range("No such element");
    }

    const Value& at(const Key& key) const
    {
      node_t* curr = find(root_->left, key);
      if (curr && curr->value.first == key)
      {
        return curr->value.second;
      }
      throw std::out_of_range("No such element");
    }

    Value& operator[](const Key& key)
    {
    }

    void prePrint(node_t* root)
    {
      if (root->left != nullptr)
      {
        prePrint(root->left);
      }
      std::cout << ' ' << root->value.second << ' ';
      if (root->right != nullptr)
      {
        prePrint(root->right);
      }
    }

    void print()
    {
      prePrint(root_);
    }

    void fixedHeight(node_t* node)
    {
      int rightH = getHeight(node->right);
      int leftH = getHeight(node->left);
      node->height = (rightH > leftH ? rightH : leftH) + 1;
    }

    int getHeight(node_t* root)
    {
      return root ? root->height : 0;
    }

    int getBalanceFactor(node_t* node)
    {
      return getHeight(node->right) - getHeight(node->left);
    }

    node_t* updateHeight(node_t* node)
    {
      node->height = 1 + std::max(node->getHeight(node->left), node->getHeight(node->right));
      return node;
    }

    node_t* insert(const std::pair< Key, Value >& value)
    {
      root_ = insert_imp(value, root_);
      return root_;
    }

    size_t size() const
    {
      return size_;
    }

    bool empty() const noexcept
    {
      return !size_;
    }

    void clear(node_t* root)
    {
      if (root)
      {
        clear(root->left);
        clear(root->right);
        delete root;
      }
    }

    void swap(Tree& other)
    {
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(cmp_, other.cmp_);
    }

    constIter cbegin() const
    {
      return constIter(minN());
    }

    constIter cend() const
    {
      return constIter(nullptr);
    }

    iter begin()
    {
      return iter(minN());
    }

    iter end()
    {
      return iter(nullptr);
    }

    ~Tree()
    {
      clear(root_);
    }

  private:
    node_t* root_;
    size_t size_;
    Compare cmp_;

    node_t* insert_imp(const std::pair< Key, Value >& value, node_t* curr)
    {
      if (curr == nullptr)
      {
        curr = new node_t(value);
      }
      if (cmp_(curr->value.first, value.first))
      {
        curr->right = insert_imp(value, curr->right);
      }
      else if (curr->value.first == value.first)
      {
        return balance(curr);
      }
      else
      {
        curr->left = insert_imp(value, curr->left);
      }
      return balance(curr);
    }

    node_t* balance(node_t* node)
    {
      fixedHeight(node);
      if (getBalanceFactor(node) == 2)
      {
        if (getBalanceFactor(node->right) < 0)
        {
          node->right = rotate_right(node->right);
        }
        return rotate_left(node);
      }
      if (getBalanceFactor(node) == -2)
      {
        if (getBalanceFactor(node->left) > 0)
        {
          node->left = rotate_left(node->left);
        }
        return rotate_right(node);
      }
      return node;
    }

    node_t* rotate_left(node_t* currRoot)
    {
      node_t* newRoot = currRoot->right;
      currRoot->right = newRoot->left;
      if (newRoot->left)
      {
        newRoot->left->parent = currRoot;
      }
      newRoot->left = currRoot;
      currRoot->parent = newRoot;
      fixedHeight(currRoot);
      fixedHeight(newRoot);
      return newRoot;
    }

    node_t* rotate_right(node_t* currRoot)
    {
      node_t* newRoot = currRoot->left;
      currRoot->left = newRoot->right;
      if (newRoot->right)
      {
        newRoot->right->parent = currRoot;
      }
      newRoot->right = currRoot;
      currRoot->parent = newRoot;
      fixedHeight(currRoot);
      fixedHeight(newRoot);
      return newRoot;
    }

    node_t* minN()
    {
      auto tmp = root_->left;
      while (tmp->left)
      {
        tmp = tmp->left;
      }
      root_ = tmp;
      return root_;
    }

  };
}

#endif
