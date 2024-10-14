#ifndef TREE_HPP
#define TREE_HPP
#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include "tree_node.hpp"
#include "const_tree_iterator.hpp"

namespace sakovskaia
{
  template < typename Key, typename Value, typename Comp = std::less< Key > >
  class Tree
  {
  public:
    Tree();
    Tree(const Tree& other);
    Tree(Tree && other) noexcept;
    ~Tree();
    Tree & operator=(const Tree & other);
    Tree & operator=(Tree && other) noexcept;
    Value & at(const Key & key);
    const Value & at(const Key & key) const;
    bool empty() const noexcept;
    bool contains(const Key & key) const;
    size_t getSize() const;
    void swap(Tree & other) noexcept;
    void push(const Key & key, const Value & value);
    ConstIterTree< Key, Value, Comp > cbegin() const;
    ConstIterTree< Key, Value, Comp > cend() const;
    ConstIterTree< Key, Value, Comp > find(const Key & key) const;

    template< typename F >
    F traverseLnr(F f) const;
    template< typename F >
    F traverseRnl(F f) const;
    template< typename F >
    F traverseBreadth(F f) const;

  private:
    size_t size_;
    detail::Node< Key, Value > * root;
    Comp comp_;
    size_t getHeight(detail::Node< Key, Value > * node) const;
    size_t getBalance(detail::Node< Key, Value > * node) const;
    detail::Node< Key, Value > * find_min(detail::Node< Key, Value > * node) const;
    detail::Node< Key, Value > * get(detail::Node< Key, Value > * node, const Key & key) const;
    Value & get(const Key & key);
    detail::Node< Key, Value > * get(detail::Node< Key, Value > * node, const Key & key);
    detail::Node< Key, Value > * balanceNode(detail::Node< Key, Value > * node);
    detail::Node< Key, Value > * insertNode(detail::Node< Key, Value > * node, const Key & key, const Value & value);
    detail::Node< Key, Value > * findNode(detail::Node< Key, Value > * node, const Key & key) const;
    void clear();
    void clearNode(detail::Node< Key, Value > * node);
  };

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp >::Tree():
    size_(0),
    root(nullptr),
    comp_(Comp())
  {}

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp >::Tree(const Tree & other):
    size_(0),
    root(nullptr),
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

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp >::Tree(Tree && other) noexcept:
    size_(other.size_),
    root(other.root),
    comp_(other.comp_)
  {
    other.size_ = 0;
    other.root = nullptr;
  }

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp >::~Tree()
  {
    clear();
  }

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp > & Tree< Key, Value, Comp >::operator=(const Tree & other)
  {
    if (this != & other)
    {
      Tree temp(other);
      swap(temp);
    }
    return * this;
  }

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp > & Tree< Key, Value, Comp >::operator=(Tree && other) noexcept
  {
    if (this != & other)
    {
      clear();
      swap(other);
    }
    return * this;
  }

  template < typename Key, typename Value, typename Comp >
  Value & Tree< Key, Value, Comp >::at(const Key & key)
  {
    auto node = findNode(root, key);
    if (!node)
    {
      throw std::out_of_range("Key not found");
    }
    return node->data.second;
  }

  template < typename Key, typename Value, typename Comp >
  const Value & Tree< Key, Value, Comp >::at(const Key & key) const
  {
    auto node = findNode(root, key);
    if (!node)
    {
      throw std::out_of_range("Key not found");
    }
    return node->data.second;
  }

  template < typename Key, typename Value, typename Comp >
  bool Tree< Key, Value, Comp >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename Key, typename Value, typename Comp >
  bool Tree< Key, Value, Comp >::contains(const Key& key) const
  {
    return get(root, key) != nullptr;
  }

  template < typename Key, typename Value, typename Comp >
  size_t Tree< Key, Value, Comp >::getSize() const
  {
    return size_;
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::push(const Key & key, const Value & value)
  {
    root = insertNode(root, key, value);
  }

  template < typename Key, typename Value, typename Comp >
  ConstIterTree< Key, Value, Comp > Tree< Key, Value, Comp >::cbegin() const
  {
    if (root != nullptr)
    {
      return ConstIterTree< Key, Value, Comp >(find_min(root));
    }
    else
    {
      return ConstIterTree< Key, Value, Comp >(nullptr);
    }
  }

  template < typename Key, typename Value, typename Comp >
  ConstIterTree< Key, Value, Comp > Tree< Key, Value, Comp >::cend() const
  {
    return ConstIterTree< Key, Value, Comp >(nullptr);
  }

  template < typename Key, typename Value, typename Comp >
  ConstIterTree< Key, Value, Comp > Tree< Key, Value, Comp >::find(const Key & key) const
  {
    return ConstIterTree< Key, Value, Comp >(findNode(root, key));
  }

  template < typename Key, typename Value, typename Comp >
  size_t Tree< Key, Value, Comp >::getHeight(detail::Node< Key, Value > * node) const
  {
    if (node == nullptr)
    {
      return 0;
    }
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
  }

  template < typename Key, typename Value, typename Comp >
  size_t Tree< Key, Value, Comp >::getBalance(detail::Node< Key, Value > * node) const
  {
    if (node != nullptr)
    {
      return getHeight(node->left) - getHeight(node->right);
    }
    else
    {
      return 0;
    }
  }

  template< typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::find_min(detail::Node< Key, Value > * node) const
  {
    while (node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  template< typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::get(detail::Node< Key, Value > * node, const Key & key) const
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
  Value & Tree< Key, Value, Comp >::get(const Key & key)
  {
    detail::Node< Key, Value > * val = get(key, root);
    return val->data.second;
  }

  template< typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::get(detail::Node< Key, Value > * node, const Key & key)
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

  template < typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::balanceNode(detail::Node< Key, Value > * node)
  {
    size_t balance = getBalance(node);
    if (balance > 1)
    {
      if (getBalance(node->left) < 0)
      {
        node->rotate_left(node);
      }
      return node->rotate_right(node);
    }
    if (balance < -1)
    {
      if (getBalance(node->right) > 0)
      {
        node->right = node->rotate_right(node->right);
      }
      return node->rotate_left(node);
    }
    return node;
  }

  template < typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::insertNode(detail::Node< Key, Value > * node, const Key & key, const Value & value)
  {
    if (node == nullptr)
    {
      detail::Node< Key, Value > * new_node = nullptr;
      try
      {
        new_node = new detail::Node< Key, Value >;
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
      node = new_node;
      ++size_;
    }
    else if (comp_(key, node->data.first))
    {
      node->left = insertNode(node->left, key, value);
      node->left->parent = node;
    }
    else if (comp_(node->data.first, key))
    {
      node->right = insertNode(node->right, key, value);
      node->right->parent = node;
    }
    else
    {
      node->data.second = value;
    }
    return balanceNode(node);
  }

  template < typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::findNode(detail::Node< Key, Value > * node, const Key & key) const
  {
    if (!node || (!comp_(key, node->data.first) && !comp_(node->data.first, key)))
    {
      return node;
    }

    if (comp_(key, node->data.first))
    {
      return findNode(node->left, key);
    }
    return findNode(node->right, key);
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::clear()
  {
    clearNode(root);
    root = nullptr;
    size_ = 0;
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::clearNode(detail::Node< Key, Value > * node)
  {
    if (!node)
    {
      return;
    }
    clearNode(node->left);
    clearNode(node->right);
    delete node;
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::swap(Tree& other) noexcept
  {
    std::swap(root, other.root);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
  }

  template< typename Key, typename Value, typename Comp >
  template< typename F>
  F Tree< Key, Value, Comp >::traverseLnr(F f) const
  {
    if (empty())
    {
      throw std::logic_error("<EMPTY>");
    }

    std::stack< detail::Node< Key, Value > * > node_stack;
    detail::Node< Key, Value > * cur = root;

    while (!node_stack.empty() || cur != nullptr)
    {
      if (cur != nullptr)
      {
        node_stack.push(cur);
        cur = cur->left;
      }
      else
      {
        cur = node_stack.top();
        node_stack.pop();
        f(cur->data);
        cur = cur->right;
      }
    }
    return f;
  }

  template< typename Key, typename Value, typename Comp >
  template< typename F >
  F Tree< Key, Value, Comp >::traverseRnl(F f) const
  {
    if (empty())
    {
      throw std::logic_error("<EMPTY>");
    }

    std::stack< detail::Node< Key, Value > * > node_stack;
    detail::Node< Key, Value > * cur = root;

    while (!node_stack.empty() || cur != nullptr)
    {
      while (cur != nullptr)
      {
        node_stack.push(cur);
        cur = cur->right;
      }
      cur = node_stack.top();
      node_stack.pop();
      f(cur->data);
      cur = cur->left;
    }
    return f;
  }

  template< typename Key, typename Value, typename Comp >
  template< typename F >
  F Tree< Key, Value, Comp >::traverseBreadth(F f) const
  {
    if (empty())
    {
      throw std::logic_error("<EMPTY>");
    }

    std::queue< detail::Node<Key, Value > * > queueOfnodes;
    queueOfnodes.push(root);

    while (!queueOfnodes.empty())
    {
      detail::Node< Key, Value > * cur = queueOfnodes.front();
      queueOfnodes.pop();
      f(cur->data);
      if (cur->left != nullptr)
      {
        queueOfnodes.push(cur->left);
      }
      if (cur->right != nullptr)
      {
        queueOfnodes.push(cur->right);
      }
    }
    return f;
  }
}

#endif
