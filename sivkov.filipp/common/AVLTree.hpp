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

    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    void remove(const Key& key);
    bool empty() const noexcept;
    bool contains(const Key& key) const;
    void swap(AVLTree other) noexcept;
    void push(const Key& key, const Value& value);
    void deleteKey(const Key& key);
    Value& operator[](const Key& key);
    const Value& operator[](const Key& key) const;

    ConstIteratorTree< Key, Value, Comp > cbegin() const;
    ConstIteratorTree< Key, Value, Comp > cend() const;
    ConstIteratorTree< Key, Value, Comp > find(const Key& key) const;

  private:
    size_t size_;
    detail::TreeNode< Key, Value >* root_;
    Comp comp_;

    void clear();
    void clear(detail::TreeNode< Key, Value >* node);
    detail::TreeNode< Key, Value >* remove(detail::TreeNode< Key, Value >* node, const Key& key);

    detail::TreeNode< Key, Value >* find_min(detail::TreeNode< Key, Value >* node) const;
    detail::TreeNode< Key, Value >* deep_copy(detail::TreeNode< Key, Value >* root);
    detail::TreeNode< Key, Value >* balance(detail::TreeNode< Key, Value >* root);
    int height(detail::TreeNode< Key, Value >* root);
    int get_balance_factor(detail::TreeNode< Key, Value >* root);

    const Value& get(const Key& key) const;
    detail::TreeNode< Key, Value >* get(detail::TreeNode< Key, Value >* node, const Key& key) const;
    Value& get(const Key& key);
    detail::TreeNode< Key, Value >* get(detail::TreeNode< Key, Value >* node, const Key& key);
    detail::TreeNode< Key, Value >* insert(detail::TreeNode< Key, Value >* root, const Key& key, const Value& value);
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
    try
    {
      for (auto it = other.cbegin(); it != other.cend(); ++it)
      {
        push(it->first, it->second);
      }
    }
    catch (...)
    {
      clear();
      throw std::logic_error("error");
    }
  }

  template< typename Key, typename Value, typename Comp >
  AVLTree< Key, Value, Comp >::AVLTree(AVLTree&& other) noexcept:
    size_(other.size_),
    root_(other.root_),
    comp_(other.comp_)
  {
    other.size_ = 0;
    other.root_ = nullptr;
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
      AVLTree< Key, Value > temp(other);
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
      clear();
      swap(temp);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Comp >
  Value& AVLTree< Key, Value, Comp >::at(const Key& key)
  {
    detail::TreeNode< Key, Value >* node = get(root_, key);
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
  const Value& AVLTree< Key, Value, Comp >::at(const Key& key) const
  {
    detail::TreeNode< Key, Value >* node = get(root_, key);
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
  bool AVLTree< Key, Value, Comp >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename Key, typename Value, typename Comp >
  bool AVLTree< Key, Value, Comp >::contains(const Key& key) const
  {
    return get(root_, key) != nullptr;
  }

  template< typename Key, typename Value, typename Comp >
  void AVLTree< Key, Value, Comp >::swap(AVLTree other) noexcept
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

  template<typename Key, typename Value, typename Comp>
  void AVLTree<Key, Value, Comp>::deleteKey(const Key& key)
  {
    if (contains(key))
    {
      root_ = remove(root_, key);
      --size_;
    }
    else
    {
      throw std::out_of_range("Error key");
    }
  }

  template< typename Key, typename Value, typename Comp >
  Value& AVLTree< Key, Value, Comp >::operator[](const Key& key)
  {
    detail::TreeNode< Key, Value >* data = get(key, root_);
    if (data)
    {
      return data->data.second;
    }
    else
    {
      push(key, Value());
      return get(key, root_)->data.second;
    }
  }

  template< typename Key, typename Value, typename Comp >
  const Value& AVLTree< Key, Value, Comp >::operator[](const Key& key) const
  {
    detail::TreeNode< Key, Value >* data = get(key, root_);
    if (data)
    {
      return data->data.second;
    }
    else
    {
      push(key, Value());
      return get(key, root_)->data.second;
    }
  }

  template< typename Key, typename Value, typename Comp >
  ConstIteratorTree< Key, Value, Comp > AVLTree< Key, Value, Comp >::cbegin() const
  {
    if (root_ != nullptr)
    {
      return ConstIteratorTree< Key, Value, Comp >(find_min(root_));
    }
    else
    {
      return ConstIteratorTree< Key, Value, Comp >(nullptr);
    }
  }

  template< typename Key, typename Value, typename Comp >
  ConstIteratorTree< Key, Value, Comp > AVLTree< Key, Value, Comp >::cend() const
  {
    return ConstIteratorTree< Key, Value, Comp >(nullptr);
  }

  template< typename Key, typename Value, typename Comp >
  ConstIteratorTree< Key, Value, Comp > AVLTree< Key, Value, Comp >::find(const Key& key) const
  {
    detail::TreeNode< Key, Value >* node = get(root_, key);
    if (node)
    {
      ConstIteratorTree< Key, Value, Comp > it(node);
      if (it.current_->data.first == key)
      {
        return it;
      }
    }
    return cend();
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
    if (node != nullptr)
    {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::remove(detail::TreeNode< Key, Value >* node, const Key& key)
  {
    if (node == nullptr)
    {
      return nullptr;
    }

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
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::balance(detail::TreeNode< Key, Value >* root)
  {
    int balance_factor = get_balance_factor(root);
    if (balance_factor > 1)
    {
      if (get_balance_factor(root->left) >= 0)
      {
        return root->rotate_right(root);
      }
      else
      {
        root->left = root->rotate_left(root->left);
        return root->rotate_right(root);
      }
    }
    else if (balance_factor < -1)
    {
      if (get_balance_factor(root->right) <= 0)
      {
        return root->rotate_left(root);
      }
      else
      {
        root->right = root->rotate_right(root->right);
        return root->rotate_left(root);
      }
    }
    return root;
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
  const Value& AVLTree< Key, Value, Comp >::get(const Key& key) const
  {
    detail::TreeNode< Key, Value >* val = get(key, root_);
    return val->data.second;
  }

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::get(detail::TreeNode< Key, Value >* node, const Key& key) const
  {
    if (node == nullptr || node->data.first == key)
    {
      return node;
    }
    if (comp_(key, node->data.first))
    {
      return get(node->left, key);
    }
    else
    {
      return get(node->right, key);
    }
  }

  template< typename Key, typename Value, typename Comp >
  Value& AVLTree< Key, Value, Comp >::get(const Key& key)
  {
    detail::TreeNode< Key, Value >* val = get(key, root_);
    return val->data.second;
  }

  template< typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::get(detail::TreeNode< Key, Value >* node, const Key& key)
  {
    if (node == nullptr || node->data.first == key)
    {
      return node;
    }
    if (comp_(key, node->data.first))
    {
      return get(node->left, key);
    }
    else
    {
      return get(node->right, key);
    }
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
    else
    {
      root->data.second = value;
    }
    return balance(root);
  }
}
#endif

