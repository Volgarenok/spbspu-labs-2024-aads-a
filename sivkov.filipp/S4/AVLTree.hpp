#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>
#include <iostream>
#include "const_iterator.hpp"
#include "node.hpp"

template < typename Key, typename Value, typename Comp = std::less< Key > >
struct AVLTree
{
  using node = Node< Key, Value >;
  AVLTree():
    size_(0),
    root_(nullptr),
    comp_(Comp())
  {}

  AVLTree(const AVLTree& other):
    size_(0),
    root_(nullptr),
    comp_(other.comp_)
  {
    root_ = deep_copy(other.root_);
  }

  AVLTree(const AVLTree&& other):
    size_(other.size_),
    root_(other.root_),
    comp_(other.comp_)
  {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  ~AVLTree()
  {
    clear();
  }

  AVLTree& operator=(const AVLTree& other)
  {
    if (this != std::addressof(other))
    {
      AVLTree< Key, Value, Comp > temp(other);
      swap(temp);
    }
    return *this;
  }

  AVLTree& operator=(const AVLTree&& other)
  {
    if (this != std::addressof(other))
    {
      swap(other);
    }
    return *this;
  }


  bool empty()
  {
    return size_ == 0;
  }

  void swap(AVLTree other)
  {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
  }

  void push(const Key& key, const Value& value)
  {
    root_ = insert(root_, key, value);
    ++size_;
  }

  void clear()
  {
    clear(root_);
    root_ = nullptr;
  }

  void clear(node* node)
  {
    if (node != nullptr)
    {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  int height(node* root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    return 1 + std::max(height(root->left), height(root->right));
  }

  int get_balance_factor(node* root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    return height(root->left) - height(root->right);
  }

  node* find(const Key& key)
  {
    return find(root_, key);
  }

  node* find(node* root, const Key& key)
  {
    if (root == nullptr || root->data.first == key)
    {
      return root;
    }

    if (comp_(key, root->data.first))
    {
      return find(root->left, key);
    }
    else
    {
      return find(root->right, key);
    }
  }

  node* insert(node* root, const Key& key, const Value& value)
  {
    if (root == nullptr)
    {
      root = new node;
      root->data = std::make_pair(key, value);
      root->left = nullptr;
      root->right = nullptr;
      root->parent = nullptr;
    }
    else if (comp_(key, root->data.first))
    {
      root->left = insert(root->left, key, value);
      root->left->parent = root;
    }
    else if (comp_(root->data.first, key))
    {
      root->right = insert(root->right, key, value);
      root->right->parent = root;
    }

    return balance(root);
  }

  node* balance(node* root)
  {
    int balance_factor = get_balance_factor(root);

    if (balance_factor > 1)
    {
      if (get_balance_factor(root->left) >= 0)
      {
        return rotate_right(root);
      }
      else
      {
        root->left = rotate_left(root->left);
        return rotate_right(root);
      }
    }
    else if (balance_factor < -1)
    {
      if (get_balance_factor(root->right) <= 0)
      {
        return rotate_left(root);
      }
      else
      {
        root->right = rotate_right(root->right);
        return rotate_left(root);
      }
    }
    return root;
  }

  node* rotate_right(node* root)
  {
    node* new_root = root->left;
    root->left = new_root->right;
    if (new_root->right != nullptr)
    {
      new_root->right->parent = root;
    }
    new_root->right = root;
    new_root->parent = root->parent;
    root->parent = new_root;
    return new_root;
  }

  node* rotate_left(node* root)
  {
    node* new_root = root->right;
    root->right = new_root->left;
    if (new_root->left != nullptr)
    {
      new_root->left->parent = root;
    }
    new_root->left = root;
    new_root->parent = root->parent;
    root->parent = new_root;
    return new_root;
  }

  node* deep_copy(node* root)
  {
    if (root == nullptr)
    {
      return nullptr;
    }
    node* new_root = new node;
    new_root->data = root->data;
    new_root->left = deep_copy(root->left);
    new_root->right = deep_copy(root->right);
    return new_root;
  }
  const_iterator cbegin() const
  {
    if (root_ == nullptr)
    {
      return const_iterator(nullptr);
    }
    return const_iterator(min_node(root_));
  }

  const_iterator cend() const
  {
    return const_iterator(nullptr);
  }

private:
  Comp comp_;
  size_t size_;
  node* root_;

  node* min_node(node* root) const
  {
    while (root->left != nullptr)
    {
      root = root->left;
    }
    return root;
  }
};
#endif
