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
    void deleteKey(const Key & key);
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
    detail::Node< Key, Value > * deleteNode(detail::Node< Key, Value > * node, const Key & key);
    detail::Node< Key, Value > * insert(detail::Node< Key, Value > * node, detail::Node< Key, Value > * parent, const Key & key, const Value & value);
    detail::Node< Key, Value > * findNode(const Key & key) const;
    detail::Node< Key, Value > * copy(detail::Node< Key, Value > * node, detail::Node< Key, Value > * parent = nullptr);
    void clear(detail::Node< Key, Value > * node);
    detail::Node< Key, Value > * findMin(detail::Node< Key, Value > * node) const;
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
    root = copy(other.root);
    size_ = other.size_;
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
    clear(root);
  }

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp > & Tree< Key, Value, Comp >::operator=(const Tree & other)
  {
    if (this != & other)
    {
      clear(root);
      root = copy(other.root);
      size_ = other.size_;
      comp_ = other.comp_;
    }
    return * this;
  }

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp > & Tree< Key, Value, Comp >::operator=(Tree && other) noexcept
  {
    if (this != & other)
    {
      clear(root);
      root = other.root;
      size_ = other.size_;
      comp_ = std::move(other.comp_);
      other.root = nullptr;
      other.size_ = 0;
    }
    return * this;
  }

  template < typename Key, typename Value, typename Comp >
  Value & Tree< Key, Value, Comp >::at(const Key & key)
  {
    auto node = findNode(key);
    if (!node)
    {
      throw std::out_of_range("Key not found");
    }
    return node->data.second;
  }

  template < typename Key, typename Value, typename Comp >
  const Value & Tree< Key, Value, Comp >::at(const Key & key) const
  {
    auto node = findNode(key);
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
  bool Tree< Key, Value, Comp >::contains(const Key & key) const
  {
    return findNode(key) != nullptr;
  }

  template < typename Key, typename Value, typename Comp >
  size_t Tree< Key, Value, Comp >::getSize() const
  {
    return size_;
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::swap(Tree & other) noexcept
  {
    std::swap(root, other.root);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::push(const Key & key, const Value & value)
  {
    root = insert(root, nullptr, key, value);
  }

  template< typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::deleteKey(const Key & key)
  {
    root = deleteNode(root, key);
  }

  template < typename Key, typename Value, typename Comp >
  ConstIterTree< Key, Value, Comp > Tree< Key, Value, Comp >::cbegin() const
  {
    return ConstIterTree< Key, Value, Comp >(findMin(root));
  }

  template < typename Key, typename Value, typename Comp >
  ConstIterTree< Key, Value, Comp > Tree< Key, Value, Comp >::cend() const
  {
    return ConstIterTree< Key, Value, Comp >(nullptr);
  }

  template < typename Key, typename Value, typename Comp >
  ConstIterTree< Key, Value, Comp > Tree< Key, Value, Comp >::find(const Key & key) const
  {
    return ConstIterTree< Key, Value, Comp >(findNode(key));
  }

  template< typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::deleteNode(detail::Node< Key, Value > * node, const Key & key)
  {
    if (!node)
    {
      return nullptr;
    }
    if (comp_(key, node->data.first))
    {
      node->left = deleteNode(node->left, key);
    }
    else if (comp_(node->data.first, key))
    {
      node->right = deleteNode(node->right, key);
    }
    else
    {
      if (!node->left)
      {
        detail::Node< Key, Value >* rightChild = node->right;
        delete node;
        --size_;
        return rightChild;
      }
      else if (!node->right)
      {
        detail::Node< Key, Value >* leftChild = node->left;
        delete node;
        --size_;
        return leftChild;
      }
      detail::Node< Key, Value >* minNode = findMin(node->right);
      node->data = minNode->data;
      node->right = deleteNode(node->right, minNode->data.first);
    }
    return node;
  }

  template < typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::insert(detail::Node< Key, Value > * node, detail::Node< Key, Value > * parent, const Key & key, const Value & value)
  {
    if (!node)
    {
      detail::Node< Key, Value > * newNode = new detail::Node< Key, Value >(key, value);
      newNode->parent = parent;
      ++size_;
      return newNode;
    }
    if (comp_(key, node->data.first))
    {
      node->left = insert(node->left, node, key, value);
    }
    else if (comp_(node->data.first, key))
    {
      node->right = insert(node->right, node, key, value);
    }
    else
    {
      node->data.second = value;
    }
    return node;
  }

  template < typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::findNode(const Key & key) const
  {
    detail::Node< Key, Value > * current = root;
    while (current)
    {
      if (comp_(key, current->data.first))
      {
        current = current->left;
      }
      else if (comp_(current->data.first, key))
      {
        current = current->right;
      }
      else
      {
        return current;
      }
    }
    return nullptr;
  }

  template < typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::copy(detail::Node< Key, Value > * node, detail::Node< Key, Value > * parent)
  {
    if (!node)
    {
      return nullptr;
    }
    detail::Node< Key, Value > * newNode = new detail::Node< Key, Value >(node->data.first, node->data.second);
    newNode->parent = parent;
    newNode->left = copy(node->left, newNode);
    newNode->right = copy(node->right, newNode);
    return newNode;
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::clear(detail::Node< Key, Value > * node)
  {
    if (node)
    {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  template < typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::findMin(detail::Node< Key, Value > * node) const
  {
    while (node && node->left)
    {
      node = node->left;
    }
    return node;
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
