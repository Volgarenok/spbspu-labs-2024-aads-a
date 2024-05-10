#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>
#include <iostream>
#include "treeNode.hpp"
#include "cIterator.hpp"

namespace sivkov
{
  template < typename Key, typename Value, typename Comp = std::less< Key > >
  struct AVLTree
  {
    AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree(AVLTree&& other) noexcept;
    ~AVLTree();

    AVLTree& operator=(const AVLTree< Key, Value, Comp >& other);
    AVLTree& operator=(AVLTree< Key, Value, Comp >&& other) noexcept;

    Value get(const Key& key);

    void clear();
    void clear(detail::TreeNode< Key, Value >* node);
    bool emty();
    bool contains(const Key& key) const;
    void swap(AVLTree other);
    void push(const Key& key, const Value& value);

    int height(detail::TreeNode< Key, Value >* root);
    int get_balance_factor(detail::TreeNode< Key, Value >* root);

    void remove(const Key& key);
    detail::TreeNode< Key, Value >* remove(detail::TreeNode< Key, Value >* node, const Key& key);

    detail::TreeNode< Key, Value >* find_min(detail::TreeNode< Key, Value >* node) const;
    detail::TreeNode< Key, Value >* deep_copy(detail::TreeNode< Key, Value >* root);

    detail::TreeNode< Key, Value >* insert( detail::TreeNode< Key, Value >* root, const Key& key, const Value& value);

    detail::TreeNode< Key, Value >* search(const Key& key) const;
    detail::TreeNode< Key, Value >* search(detail::TreeNode< Key, Value >* node, const Key& key) const;

    detail::TreeNode< Key, Value >* rotate_right( detail::TreeNode< Key, Value >* root);
    detail::TreeNode< Key, Value >* rotate_left( detail::TreeNode< Key, Value >* root);
    detail::TreeNode< Key, Value >* balance( detail::TreeNode< Key, Value >* root);

    ConstIterator< Key, Value, Comp > cbegin() const;
    ConstIterator< Key, Value, Comp > cend() const;
    ConstIterator< Key, Value, Comp > find(const Key& key) const;

  private:
    Comp comp_;
    size_t size_;
    detail::TreeNode< Key, Value >* root_;
  };


  template< typename Key, typename Value, typename Comp >
  AVLTree< Key, Value, Comp >::AVLTree():
    size_(0),
    root_(nullptr),
    comp_(Comp())
  {}

  template< typename Key, typename Value, typename Comp >
  AVLTree< Key, Value, Comp >::AVLTree(const AVLTree& other):
    size_(0),
    root_(nullptr),
    comp_(other.comp_)
  {
    for (auto it = other.cbegin(); it != other.cend(); ++it)
    {
      push(it->first, it->second);
    }
  }

  template< typename Key, typename Value, typename Comp >
  AVLTree< Key, Value, Comp >::AVLTree(AVLTree&& other) noexcept:
    size_(other.size_),
    root_(other.root_),
    comp_(other.comp_)
  {
    other.size_ = 0;
    other.root_ = new  detail::TreeNode< Key, Value >();
  }

  template< typename Key, typename Value, typename Comp >
  AVLTree< Key, Value, Comp >::~AVLTree()
  {
    clear();
  }

  template< typename Key, typename Value, typename Comp >
  AVLTree< Key, Value, Comp >& AVLTree< Key, Value, Comp >::operator=(const AVLTree< Key, Value, Comp >& other)
  {
    AVLTree< Key, Value, Comp > temp(other);
    if (this != std::addressof(other))
    {
      swap(temp);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Comp >
  AVLTree< Key, Value, Comp >& AVLTree< Key, Value, Comp >::operator=(AVLTree< Key, Value, Comp >&& other) noexcept
  {
    AVLTree< Key, Value, Comp > temp(std::move(other));
    if (this != std::addressof(other))
    {
      swap(temp);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Comp >
  Value AVLTree< Key, Value, Comp >::get(const Key& key)
  {
     detail::TreeNode< Key, Value >* node = search(root_, key);
    if (node)
    {
      return node->data.second;
    }
    else
    {
      throw std::out_of_range("no key");
    }
  }


  template< typename Key, typename Value, typename Comp >
  void AVLTree< Key, Value, Comp >::remove(const Key& key)
  {
    root_ = remove(root_, key);
  }

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::remove(detail::TreeNode< Key, Value >* node, const Key& key)
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
        detail::TreeNode< Key, Value >* right_child = node->right;
        delete node;
        return right_child;
      }
      else if (node->right == nullptr)
      {
        detail::TreeNode< Key, Value >* left_child = node->left;
        delete node;
        return left_child;
      }
      else
      {
        detail::TreeNode< Key, Value >* successor = find_min(node->right);
        node->data = successor->data;
        node->right = remove(node->right, successor->data.first);
      }
    }

    return balance(node);
  }

  template< typename Key, typename Value, typename Comp >
  void AVLTree< Key, Value, Comp >::clear()
  {
    clear(root_);
    root_ = nullptr;
    size_ = 0;
  }

  template< typename Key, typename Value, typename Comp >
  void AVLTree< Key, Value, Comp >::clear(detail::TreeNode< Key, Value >* node)
  {
    if (node == nullptr)
    {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

  template< typename Key, typename Value, typename Comp >
  bool AVLTree< Key, Value, Comp >::emty()
  {
    return size_ == 0;
  }

  template< typename Key, typename Value, typename Comp >
  bool AVLTree< Key, Value, Comp >::contains(const Key& key) const
  {
    return search(root_, key) != nullptr;
  }

  template< typename Key, typename Value, typename Comp >
  void AVLTree< Key, Value, Comp >::swap(AVLTree other)
  {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
  }

  template< typename Key, typename Value, typename Comp >
  void AVLTree< Key, Value, Comp >::push(const Key& key, const Value& value)
  {
    root_ = insert(root_, key, value);
    ++size_;
  }

  template< typename Key, typename Value, typename Comp >
  int AVLTree< Key, Value, Comp >::height(detail::TreeNode< Key, Value >* root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    return 1 + std::max(height(root->left), height(root->right));
  }

  template< typename Key, typename Value, typename Comp >
  int AVLTree< Key, Value, Comp >::get_balance_factor(detail::TreeNode< Key, Value >* root)
  {
    if (root == nullptr)
    {
      return 0;
    }
    return height(root->left) - height(root->right);
  }

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::find_min(detail::TreeNode< Key, Value >* node) const
  {
    while (node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::deep_copy(detail::TreeNode< Key, Value >* root)
  {

    if (root == nullptr)
    {
      return nullptr;
    }
    detail::TreeNode< Key, Value >* new_root = new detail::TreeNode< Key, Value >;
    new_root->data = root->data;
    new_root->left = deep_copy(root->left);
    new_root->right = deep_copy(root->right);
    return new_root;

  }

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::insert(detail::TreeNode< Key, Value >* root,
    const Key& key, const Value& value)
  {
    if (root == nullptr)
    {
      root = new  detail::TreeNode< Key, Value >;
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

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::search(const Key& key) const
  {
    return search(root_, key);
  }

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value>* AVLTree< Key, Value, Comp >::search(detail::TreeNode< Key, Value >* node, const Key& key) const
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

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::rotate_right(detail::TreeNode< Key, Value >* root)
  {
    detail::TreeNode< Key, Value >* new_root = root->left;
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

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::rotate_left(detail::TreeNode< Key, Value >* root)
  {
    detail::TreeNode< Key, Value >* new_root = root->right;
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

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::balance(detail::TreeNode< Key, Value >* root)
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

  template< typename Key, typename Value, typename Comp >
  ConstIterator< Key, Value, Comp > AVLTree< Key, Value, Comp >::cbegin() const
  {
    if (root_ != nullptr)
    {
      return ConstIterator<Key, Value, Comp>(find_min(root_));
    }
    else
    {
      return ConstIterator<Key, Value, Comp>(nullptr);
    }
  }

  template< typename Key, typename Value, typename Comp >
  ConstIterator< Key, Value, Comp > AVLTree< Key, Value, Comp >::cend() const
  {
    return ConstIterator< Key, Value, Comp >(nullptr);
  }

  template< typename Key, typename Value, typename Comp >
  ConstIterator< Key, Value, Comp > AVLTree< Key, Value, Comp >::find(const Key& key) const
  {
    detail::TreeNode< Key, Value >* node = search(root_, key);
    if (node)
    {
      ConstIterator< Key, Value, Comp > it(node);
      if (it.getCurrent()->data.first == key)
      {
        return it;
      }
    }
    return cend();
  }
}
#endif
