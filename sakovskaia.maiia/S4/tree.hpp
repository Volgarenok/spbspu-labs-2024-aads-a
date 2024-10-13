#ifndef TREE_HPP
#define TREE_HPP
#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include "node.hpp"
#include "const_iterator.hpp"

namespace sakovskaia
{
  template < typename Key, typename Value, typename Comp = std::less< Key > >
  class Tree
  {
  public:
    Tree();
    Tree(const Tree & other);
    Tree(Tree && other) noexcept;
    ~Tree();
    Tree & operator=(const Tree & other);
    Tree & operator=(Tree && other) noexcept;
    Value & at(const Key & key);
    const Value & at(const Key & key) const;
    bool empty() const noexcept;
    bool contains(const Key & key) const;
    size_t getSize() const;
    void swap(Tree& other) noexcept;
    void push(const Key & key, const Value & value);
    ConstIterTree< Key, Value, Comp > cbegin() const;
    ConstIterTree< Key, Value, Comp > cend() const;
    ConstIterTree< Key, Value, Comp > find(const Key & key) const;

  private:
    size_t size_;
    detail::TreeNode< Key, Value > * root_;
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
    root_(nullptr),
    comp_(Comp())
  {}

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp >::Tree(const Tree & other):
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

  template < typename Key, typename Value, typename Comp >
  Tree< Key, Value, Comp >::Tree(Tree && other) noexcept:
    size_(other.size_),
    root_(other.root_),
    comp_(other.comp_)
  {
    other.size_ = 0;
    other.root_ = nullptr;
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
    auto node = findNode(root_, key);
    if (!node)
    {
      throw std::out_of_range("Key not found");
    }
    return node->data.second;
  }

  template < typename Key, typename Value, typename Comp >
  const Value & Tree< Key, Value, Comp >::at(const Key & key) const
  {
    auto node = findNode(root_, key);
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
    return get(root_, key) != nullptr;
  }

  template < typename Key, typename Value, typename Comp >
  size_t Tree< Key, Value, Comp >::getSize() const
  {
    return size_;
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::push(const Key & key, const Value & value)
  {
    root_ = insertNode(root_, key, value);
  }

  template < typename Key, typename Value, typename Comp >
  ConstIterTree< Key, Value, Comp > Tree< Key, Value, Comp >::cbegin() const
  {
    if (root_ != nullptr)
    {
      return ConstIterTree< Key, Value, Comp >(find_min(root_));
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
    return ConstIterTree< Key, Value, Comp >(findNode(root_, key));
  }

  template < typename Key, typename Value, typename Comp >
  size_t Tree< Key, Value, Comp >::getHeight(detail::Node< Key, Value > * node) const
  {
    if (node == nullptr)
    {
      return 0;
    }
    return 1 + std::max(getHeight(node->left_), getHeight(node->right_));
  }

  template < typename Key, typename Value, typename Comp >
  size_t Tree< Key, Value, Comp >::getBalance(detail::Node< Key, Value > * node) const
  {
    if (node != nullptr)
    {
      return getHeight(node->left_) - getHeight(node->right_);
    }
    else
    {
      return 0;
    }
  }

  template< typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::find_min(detail::Node< Key, Value > * node) const
  {
    while (node->left_ != nullptr)
    {
      node = node->left_;
    }
    return node;
  }

  template< typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::get(detail::Node< Key, Value > * node, const Key & key) const
  {
    if (node == nullptr || (!comp_(key, node->data_.first) && !comp_(node->data_.first, key)))
    {
      return node;
    }
    if (comp_(key, node->data_.first))
    {
      return get(node->left_, key);
    }
    else
    {
      return get(node->right_, key);
    }
  }

  template< typename Key, typename Value, typename Comp >
  Value & Tree< Key, Value, Comp >::get(const Key & key)
  {
    detail::Node< Key, Value > * val = get(key, root_);
    return val->data_.second;
  }

  template< typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::get(detail::Node< Key, Value > * node, const Key & key)
  {
    if (node == nullptr || node->data_.first == key)
    {
      return node;
    }
    if (comp_(key, node->data_.first))
    {
      return get(node->left_, key);
    }
    else
    {
      return get(node->right_, key);
    }
  }

  template < typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::balanceNode(detail::Node< Key, Value > * node)
  {
    size_t balance = getBalance(node);
    if (balance > 1)
    {
      if (getBalance(node->left_) < 0)
      {
        node->rotate_left(node);
      }
      return node->rotate_right(node);
    }
    if (balance < -1)
    {
      if (getBalance(node->right_) > 0)
      {
        node->right_ = node->rotate_right(node->right_);
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
        new_node->data_ = std::make_pair(key, value);
        new_node->left_ = nullptr;
        new_node->right_ = nullptr;
        new_node->parent_ = nullptr;
      }
      catch (...)
      {
        delete new_node;
        throw;
      }
      node = new_node;
      ++size_;
    }
    else if (comp_(key, node->data_.first))
    {
      node->left_ = insertNode(node->left_, key, value);
      node->left_->parent_ = node;
    }
    else if (comp_(node->data_.first, key))
    {
      node->right_ = insertNode(node->right_, key, value);
      node->right_->parent_ = node;
    }
    else
    {
      node->data_.second = value;
    }
    return balanceNode(node);
  }

  template < typename Key, typename Value, typename Comp >
  detail::Node< Key, Value > * Tree< Key, Value, Comp >::findNode(detail::Node< Key, Value > * node, const Key & key) const
  {
    if (!node || (!comp_(key, node->data_.first) && !comp_(node->data_.first, key)))
    {
      return node;
    }

    if (comp_(key, node->data_.first))
    {
      return findNode(node->left_, key);
    }
    return findNode(node->right_, key);
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::clear()
  {
    clearNode(root_);
    root_ = nullptr;
    size_ = 0;
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::clearNode(detail::Node< Key, Value > * node)
  {
    if (!node)
    {
      return;
    }
    clearNode(node->left_);
    clearNode(node->right_);
    delete node;
  }

  template < typename Key, typename Value, typename Comp >
  void Tree< Key, Value, Comp >::swap(Tree & other) noexcept
  {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
  }
}
