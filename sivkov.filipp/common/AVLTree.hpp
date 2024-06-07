#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>
#include <iostream>
#include "queue.hpp"
#include "stack.hpp"
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
    bool empty() const noexcept;
    bool contains(const Key& key) const;
    void swap(AVLTree& other) noexcept;
    void push(const Key& key, const Value& value);
    void deleteKey(const Key& key);
    Value& operator[](const Key& key);
    const Value& operator[](const Key& key) const;

    ConstIteratorTree< Key, Value, Comp > cbegin() const;
    ConstIteratorTree< Key, Value, Comp > cend() const;

    ConstIteratorTree< Key, Value, Comp > find(const Key& key) const;

    template< typename F >
    F traverse_lnr(F f) const;
    template< typename F >
    F traverse_rnl (F f) const;
    template< typename F >
    F traverse_breadth (F f) const;

    size_t getSize() const;

  private:
    size_t size_;
    detail::TreeNode< Key, Value >* root_;
    Comp comp_;

    void clear();
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
    detail::TreeNode< Key, Value >* addOrFind(detail::TreeNode< Key, Value >* node, const Key& key, const Value& value);
  };

  template<typename Key, typename Value, typename Comp>
  size_t AVLTree<Key, Value, Comp>::getSize() const
  {
    return size_;
  }

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
      throw;
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
    if (this != std::addressof(other))
    {
      AVLTree< Key, Value, Comp > temp(other);
      swap(temp);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Comp >
  AVLTree< Key, Value, Comp >& AVLTree< Key, Value, Comp >::operator=(AVLTree< Key, Value, Comp >&& other) noexcept
  {
    if (this != std::addressof(other))
    {
      clear();
      swap(other);
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
  void AVLTree< Key, Value, Comp >::swap(AVLTree& other) noexcept
  {
    static_assert(std::is_nothrow_copy_constructible< Comp >::value);
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
  void AVLTree< Key, Value, Comp >::deleteKey(const Key& key)
  {
    root_ = remove(root_, key);
  }

  template< typename Key, typename Value, typename Comp >
  Value& AVLTree< Key, Value, Comp >::operator[](const Key& key)
  {
    detail::TreeNode< Key, Value >* node = addOrFind(root_, key, Value());
    return node->data.second;
  }

  template< typename Key, typename Value, typename Comp >
  const Value& AVLTree< Key, Value, Comp >::operator[](const Key& key) const
  {
    detail::TreeNode< Key, Value> * node = get(root_, key);
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
    if (node && !comp_(node->data.first, key) && !comp_(key, node->data.first))
    {
      return ConstIteratorTree< Key, Value, Comp >(node);
    }
    return cend();
  }


  template< typename Key, typename Value, typename Comp >
  void AVLTree< Key, Value, Comp >::clear()
  {
    while (root_ != nullptr)
    {
      root_ = remove(root_, root_->data.first);
    }
    size_ = 0;
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
        --size_;
        return right_child;
      }
      else if (node->right == nullptr)
      {
        detail::TreeNode< Key, Value >* left_child = node->left;
        delete node;
        --size_;
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
    detail::TreeNode< Key, Value >* new_root = nullptr;
    try
    {
      new_root = new detail::TreeNode< Key, Value >;
      new_root->data = root->data;
      new_root->left = deep_copy(root->left);
      new_root->right = deep_copy(root->right);
      if (new_root->left)
      {
        new_root->left->parent = new_root;
      }
      if (new_root->right)
      {
        new_root->right->parent = new_root;
      }
    }
    catch (...)
    {
      delete new_root;
      throw;
    }
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
    if (node == nullptr || (!comp_(key, node->data.first) && !comp_(node->data.first, key)))
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
      detail::TreeNode< Key, Value >* new_node = nullptr;
      try
      {
        new_node = new detail::TreeNode< Key, Value >;
        new_node->data = std::make_pair(key, value);
        new_node->left = nullptr;
        new_node->right = nullptr;
        new_node->parent = nullptr;
      }
      catch (...)
      {
        delete new_node;
        throw;
      }
      root = new_node;
      ++size_;
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
  template < typename Key, typename Value, typename Comp >
  detail::TreeNode< Key, Value >* AVLTree< Key, Value, Comp >::addOrFind(detail::TreeNode< Key, Value >* node,
    const Key& key, const Value& value)
  {
    if (node == nullptr)
    {
      detail::TreeNode< Key, Value >* new_node = nullptr;
      try
      {
        new_node = new detail::TreeNode< Key, Value >;
        new_node->data = std::make_pair(key, value);
        new_node->left = nullptr;
        new_node->right = nullptr;
        new_node->parent = nullptr;
        if (root_ == nullptr)
        {
          root_ = new_node;
        }
        ++size_;
      }
      catch (...)
      {
        delete new_node;
        throw;
      }
      return new_node;
    }

    if (comp_(key, node->data.first))
    {
      if (node->left == nullptr)
      {
        detail::TreeNode< Key, Value >* new_node = nullptr;
        try
        {
          new_node = new detail::TreeNode< Key, Value >;
          new_node->data = std::make_pair(key, value);
          new_node->left = nullptr;
          new_node->right = nullptr;
          new_node->parent = node;
          node->left = new_node;
          ++size_;
        }
        catch (...)
        {
          delete new_node;
          throw;
        }
        return new_node;
      }
      else
      {
        return addOrFind(node->left, key, value);
      }
    }
    else if (comp_(node->data.first, key))
    {
      if (node->right == nullptr)
      {
        detail::TreeNode< Key, Value >* new_node = nullptr;
        try
        {
          new_node = new detail::TreeNode< Key, Value >;
          new_node->data = std::make_pair(key, value);
          new_node->left = nullptr;
          new_node->right = nullptr;
          new_node->parent = node;
          node->right = new_node;
          ++size_;
        }
        catch (...)
        {
          delete new_node;
          throw;
        }
        return new_node;
      }
      else
      {
        return addOrFind(node->right, key, value);
      }
    }
    else
    {
      return node;
    }
  }

  template< typename Key, typename Value, typename Comp >
  template< typename F>
  F AVLTree< Key, Value, Comp >::traverse_lnr(F f) const
  {
    if (empty())
    {
      throw std::logic_error("<EMPTY>");
    }

    Stack< detail::TreeNode< Key, Value >* > node_stack;
    detail::TreeNode< Key, Value >* current = root_;

    while (!node_stack.empty() || current != nullptr)
    {
      if (current != nullptr)
      {
        node_stack.push(current);
        current = current->left;
      }
      else
      {
        current = node_stack.top();
        node_stack.pop();
        f(current->data);
        current = current->right;
      }
    }
    return f;
  }

  template< typename Key, typename Value, typename Comp >
  template< typename F >
  F AVLTree< Key, Value, Comp >::traverse_rnl(F f) const
  {
    if (empty())
    {
      throw std::logic_error("<EMPTY>");
    }

    Stack< detail::TreeNode< Key, Value >* > node_stack;
    detail::TreeNode< Key, Value >* current = root_;

    while (!node_stack.empty() || current != nullptr)
    {
      while (current != nullptr)
      {
        node_stack.push(current);
        current = current->right;
      }
      current = node_stack.top();
      node_stack.pop();
      f(current->data);
      current = current->left;
    }
    return f;
  }


  template< typename Key, typename Value, typename Comp >
  template< typename F >
  F AVLTree< Key, Value, Comp >::traverse_breadth(F f) const
  {
    if (empty())
    {
      throw std::logic_error("<EMPTY>");
    }

    Queue< detail::TreeNode<Key, Value >* > nodes_queue;
    nodes_queue.push(root_);

    while (!nodes_queue.empty())
    {
      detail::TreeNode< Key, Value >* current = nodes_queue.front();
      nodes_queue.pop();
      f(current->data);
      if (current->left != nullptr)
      {
        nodes_queue.push(current->left);
      }
      if (current->right != nullptr)
      {
        nodes_queue.push(current->right);
      }
    }
    return f;
  }

}
#endif

