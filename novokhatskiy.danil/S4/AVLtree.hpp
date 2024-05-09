#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "AVLtreeNode.hpp"

namespace novokhatskiy
{
  template <class Key, class Value, class Compare = std::less<Key>>
  class Tree
  {
  public:
    using node_t = detail::NodeTree<Key, Value>;
    using v_type = std::pair<Key, Value>;
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

    Tree(const Tree &other) : root_(other.root_),
                              size_(other.size_),
                              cmp_(other.cmp_)
    {
      other.root_ = nullptr;
      other.size_ = 0;
    }

    Tree &operator=(const Tree &other)
    {
      if (this != std::addressof(other))
      {
        Tree<Key, Value> tmp(other);
        swap(tmp);
      }
      return *this;
    }

    Tree &operator=(Tree &&other)
    {
      if (this != std::addressof(other))
      {
        swap(other);
      }
      return *this;
    }

    node_t *rotate_left()
    {
      node_t *currRoot = this;
      node_t *newRoot = currRoot->right;
      currRoot->right = newRoot->left;
      /*node_t* newRoot = node->right;
      node_t* tmp = newRoot->left;
      node->right = tmp;
      newRoot->left = node;
      newRoot = updateHeight(newRoot);
      node = updateHeight(node);
      return newRoot;*/

      /*node_t* newRoot = node->right;
      node->right = newRoot->left;
      newRoot->right = node;
      node->parent = newRoot;
      node->right->parent = node;*/
    }

    node_t *find(node_t *node, const Key &key)
    {
      node_t *root = (node->height < 0) ? node->left : node;
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

    Value &at(const Key &key)
    {
      node_t *curr = find(root_->left, key);
      if (curr && curr->value.first == key)
      {
        return curr->value.second;
      }
      throw std::out_of_range("No such element");
    }

    const Value &at(const Key &key) const
    {
      node_t *curr = find(root_->left, key);
      if (curr && curr->value.first == key)
      {
        return curr->value.second;
      }
      throw std::out_of_range("No such element");
    }

    Value &operator[](const Key &key)
    {
    }

    node_t *rotate_right(node_t *node)
    {
      node_t *newRoot = node->left;
      node_t *tmp = newRoot->right;
      node->left = tmp;
      newRoot->right = node;
      node = updateHeight(node);
      // fixedHeight
      newRoot = updateHeight(newRoot);
      // fixheight
      return newRoot;
    }

    void prePrint(node_t *root)
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

    node_t *balance(node_t *node)
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

    void fixedHeight(node_t *node)
    {
      int rightH = getHeight(node->right);
      int leftH = getHeight(node->left);
      node->height = (rightH > leftH ? rightH : leftH) + 1;
    }

    int getHeight(node_t *root)
    {
      return root ? root->height : 0;
    }

    int getBalanceFactor(node_t *node)
    {
      return getHeight(node->right) - getHeight(node->left);
    }

    node_t *updateHeight(node_t *node)
    {
      node->height = 1 + std::max(node->getHeight(node->left), node->getHeight(node->right));
      return node;
    }

    void insert(const std::pair<Key, Value> &value)
    {
      node_t *curr = this;
      if (curr == nullptr)
      {
        curr = new node_t(value);
      }
      // sort by keys
      if (curr->value.first < value.first)
      {
        curr->right = insert(value, curr->right);
      }
      else if (curr->value.first == value.first)
      {
        return balance(curr);
      }
      else
      {
        curr->left = insert(value, curr->left);
      }
      return balance(curr);
    }

    size_t size() const
    {
      return size_;
    }

    bool empty() const noexcept
    {
      return !size_;
    }

    void clear()
    {
    }

    void swap(Tree &other)
    {
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(cmp_, other.cmp_);
    }

  private:
    node_t *root_;
    size_t size_;
    Compare cmp_;
  };
}

#endif
