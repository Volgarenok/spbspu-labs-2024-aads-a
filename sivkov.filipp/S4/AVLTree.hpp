#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>
#include <iostream>
#include "TreeNode.hpp"
#include "cIterator.hpp"


template < typename Key, typename Value, typename Comp = std::less< Key > >
struct AVLTree
{
  AVLTree();
  AVLTree(const AVLTree& other);
  AVLTree(AVLTree&& other) noexcept;
  ~AVLTree();

  AVLTree& operator=(const AVLTree<Key, Value, Comp>& other);
  AVLTree& operator=(AVLTree<Key, Value, Comp>&& other) noexcept;
  Value& operator[](const Key& key);
  void clear();
  void clear(TreeNode<Key, Value>* node);

  void remove(const Key& key);
  TreeNode< Key, Value >* remove(TreeNode<Key, Value>* node, const Key& key);

  TreeNode< Key, Value >* find_min(TreeNode<Key, Value>* node) const;

  TreeNode< Key, Value >* insert(TreeNode< Key, Value >* root, const Key& key, const Value& value);

  TreeNode< Key, Value >* search(const Key& key);
  TreeNode< Key, Value >* search(TreeNode<Key, Value>* node, const Key& key);

  TreeNode< Key, Value >* rotate_right(TreeNode< Key, Value >* root);
  TreeNode< Key, Value >* rotate_left(TreeNode< Key, Value >* root);
  TreeNode< Key, Value >* balance(TreeNode< Key, Value >* root);

  ConstIterator< Key, Value> cbegin() const;
  ConstIterator< Key, Value> cend() const;

private:
  Comp comp_;
  size_t size_;
  TreeNode< Key, Value >* root_;
};


template<typename Key, typename Value, typename Comp>
AVLTree<Key, Value, Comp>::AVLTree():
  size_(0),
  root_(nullptr),
  comp_(Comp())
{}

template<typename Key, typename Value, typename Comp>
AVLTree<Key, Value, Comp>::AVLTree(const AVLTree& other):
  size_(other.size_),
  root_(new TreeNode< Key, Value >< Key, Value >()),
  comp_(other.comp_)
{
  root_ = deep_copy(other.root_);
}

template<typename Key, typename Value, typename Comp>
AVLTree<Key, Value, Comp>::AVLTree(AVLTree&& other) noexcept:
  size_(other.size_),
  root_(other.root_),
  comp_(other.comp_)
{
  other.size_ = 0;
  other.root_ = new TreeNode< Key, Value >< Key, Value >();
}

template<typename Key, typename Value, typename Comp>
AVLTree<Key, Value, Comp>::~AVLTree()
{
  clear();
}

template<typename Key, typename Value, typename Comp>
AVLTree<Key, Value, Comp>& AVLTree<Key, Value, Comp>::operator=(const AVLTree<Key, Value, Comp>& other)
{
  AVLTree< Key, Value, Comp > temp(other);
  if (this != std::addressof(other))
  {
    swap(temp);
  }
  return *this;
}

template<typename Key, typename Value, typename Comp>
AVLTree<Key, Value, Comp>& AVLTree<Key, Value, Comp>::operator=(AVLTree<Key, Value, Comp>&& other) noexcept
{
  AVLTree< Key, Value, Comp > temp(std::move(other));
  if (this != std::addressof(other))
  {
    swap(temp);
  }
  return *this;
}

template<typename Key, typename Value, typename Comp>
Value& AVLTree<Key, Value, Comp>::operator[](const Key& key)
{
  TreeNode<Key, Value>* node = search(root_, key);
  if (node != nullptr)
  {
    return node->data.second;
  }
  else
  {
    insert(key, Value());
    return search(root_, key)->data.second;
  }
}

template<typename Key, typename Value, typename Comp>
void AVLTree<Key, Value, Comp>::remove(const Key& key)
{
  root_ = remove(root_, key);
}

template<typename Key, typename Value, typename Comp>
TreeNode<Key, Value>* AVLTree<Key, Value, Comp>::remove(TreeNode<Key, Value>* node, const Key& key)
{
  if (node == nullptr)
    return nullptr;

  if (comp_(key, node->data.first))
  {
    node->left = remove(node->left, key);
  }
  else if (comp_(node->data.first, key))
  {
    node->right = remove(node->right, key);
  }
  else
  {
    if (node->left == nullptr)
    {
      TreeNode<Key, Value>* right_child = node->right;
      delete node;
      return right_child;
    }
    else if (node->right == nullptr)
    {
      TreeNode<Key, Value>* left_child = node->left;
      delete node;
      return left_child;
    }
    else
    {
      TreeNode<Key, Value>* successor = find_min(node->right);
      node->data = successor->data;
      node->right = remove(node->right, successor->data.first);
    }
  }

  return balance(node);
}

template<typename Key, typename Value, typename Comp>
void AVLTree<Key, Value, Comp>::clear()
{
  clear(root_);
  root_ = nullptr;
  size_ = 0;
}

template<typename Key, typename Value, typename Comp>
void AVLTree<Key, Value, Comp>::clear(TreeNode<Key, Value>* node)
{
  clear(node->left);
  clear(node->right);
  delete node;
}

template<typename Key, typename Value, typename Comp>
TreeNode<Key, Value>* AVLTree<Key, Value, Comp>::find_min(TreeNode<Key, Value>* node) const
{
  while (node->left != nullptr)
  {
    node = node->left;
  }
  return node;
}

template<typename Key, typename Value, typename Comp>
TreeNode< Key, Value >* AVLTree<Key, Value, Comp>::insert(TreeNode< Key, Value >* root, const Key& key, const Value& value)
{
  if (root == nullptr)
  {
    root = new TreeNode< Key, Value >;
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

template<typename Key, typename Value, typename Comp>
TreeNode<Key, Value>* AVLTree<Key, Value, Comp>::search(const Key& key)
{
  return search(root_, key);
}

template<typename Key, typename Value, typename Comp>
TreeNode<Key, Value>* AVLTree<Key, Value, Comp>::search(TreeNode<Key, Value>* node, const Key& key)
{
  if (node == nullptr || node->data.first == key)
  {
    return node;
  }
  if (comp_(key, node->data.first))
  {
    return search(node->left, key);
  }
  else
  {
    return search(node->right, key);
  }
}

template<typename Key, typename Value, typename Comp>
TreeNode< Key, Value >* AVLTree<Key, Value, Comp>::rotate_right(TreeNode< Key, Value >* root)
{
  TreeNode< Key, Value >* new_root = root->left;
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

template<typename Key, typename Value, typename Comp>
TreeNode< Key, Value >* AVLTree<Key, Value, Comp>::rotate_left(TreeNode< Key, Value >* root)
{
  TreeNode< Key, Value >* new_root = root->right;
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

template<typename Key, typename Value, typename Comp>
TreeNode< Key, Value >* AVLTree<Key, Value, Comp>::balance(TreeNode< Key, Value >* root)
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

template<typename Key, typename Value, typename Comp>
ConstIterator<Key, Value> AVLTree<Key, Value, Comp>::cbegin() const
{
  return AVLTreeConstIterator<Key, Value>(root_ != nullptr ? find_min(root_) : nullptr);
}

template<typename Key, typename Value, typename Comp>
ConstIterator<Key, Value> AVLTree<Key, Value, Comp>::cend() const
{
  return AVLTreeConstIterator<Key, Value>(nullptr);
}

#endif
