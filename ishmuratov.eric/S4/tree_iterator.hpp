#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "tree_node.hpp"
#include <memory>

namespace ishmuratov
{
  template< class Key, class Value, class Comparator >
  class AVLTree;

  template< class Key, class Value, class Comparator = std::less< Key > >
  class Iterator
  {
    using tnode = detail::TNode< Key, Value >;
    using Iter = Iterator< Key, Value, Comparator >;
    using pair = std::pair< Key, Value >;
  public:
    Iterator():
      node_(nullptr)
    {}

    ~Iterator() = default;
    Iterator(const Iter &) = default;
    Iter & operator=(const Iter &) = default;
    Iter & operator=(Iter &&) = default;

    Iter & operator++()
    {
      if (node_ == nullptr)
      {
        return *this;
      }
      if (node_->right != nullptr)
      {
        node_ = min_elem(node_->right);
      }
      else
      {
        auto parent = node_->parent;
        while (parent != nullptr && node_ == parent->right)
        {
          node_ = parent;
          parent = parent->parent;
        }
        node_ = parent;
      }
      return *this;
    }

    Iter & operator--()
    {
      if (node_ == nullptr)
      {
        return *this;
      }
      if (node_->left != nullptr)
      {
        node_ = min_elem(node_->left);
      }
      else
      {
        auto parent = node_->parent;
        while (parent != nullptr && node_ == parent->left)
        {
          node_ = parent;
          parent = parent->parent;
        }
        node_ = parent;
      }
      return *this;
    }

    Iter operator++(int)
    {
      Iter result(*this);
      ++(*this);
      return result;
    }

    Iter operator--(int)
    {
      Iter result(*this);
      --(*this);
      return result;
    }

    pair & operator*()
    {
      return node_->data;
    }

    const pair & operator*() const
    {
      return node_->data;
    }

    pair * operator->()
    {
      return std::addressof(node_->data);
    }

    const pair * operator->() const
    {
      return std::addressof(node_->data);
    }

    bool operator==(const Iter & rhs) const
    {
      return node_ == rhs.node_;
    }

    bool operator!=(const Iter & rhs) const
    {
      return node_ != rhs.node_;
    }

  private:
    friend AVLTree< Key, Value, Comparator >;
    detail::TNode< Key, Value > * node_;
    explicit Iterator(detail::TNode< Key, Value > * node):
      node_(node)
    {}

    tnode * min_elem(tnode * root) const
    {
      if (root == nullptr || root->left == nullptr)
      {
        return root;
      }
      return min_elem(root->left);
    }
  };

  template< class Key, class Value, class Comparator = std::less< Key > >
  class ConstIterator
  {
    using tnode = detail::TNode< Key, Value >;
    using ConstIter = ConstIterator< Key, Value, Comparator >;
    using pair = std::pair< Key, Value >;
  public:
    ConstIterator():
      node_(nullptr)
    {}

    ~ConstIterator() = default;
    ConstIterator(const ConstIter &) = default;
    ConstIter & operator=(const ConstIter &) = default;
    ConstIter & operator=(ConstIter &&) = default;

    ConstIter & operator++()
    {
      if (node_ == nullptr)
      {
        return *this;
      }
      if (node_->right != nullptr)
      {
        node_ = min_elem(node_->right);
      }
      else
      {
        auto parent = node_->parent;
        while (parent != nullptr && node_ == parent->right)
        {
          node_ = parent;
          parent = parent->parent;
        }
        node_ = parent;
      }
      return *this;
    }

    ConstIter & operator--()
    {
      if (node_ == nullptr)
      {
        return *this;
      }
      if (node_->left != nullptr)
      {
        node_ = min_elem(node_->left);
      }
      else
      {
        auto parent = node_->parent;
        while (parent != nullptr && node_ == parent->left)
        {
          node_ = parent;
          parent = parent->parent;
        }
        node_ = parent;
      }
      return *this;
    }

    ConstIter operator++(int)
    {
      ConstIter result(*this);
      ++(*this);
      return result;
    }

    ConstIter operator--(int)
    {
      ConstIter result(*this);
      --(*this);
      return result;
    }

    const pair & operator*() const
    {
      return node_->data;
    }

    const pair * operator->() const
    {
      return std::addressof(node_->data);
    }

    bool operator==(const ConstIter & rhs) const
    {
      return node_ == rhs.node_;
    }

    bool operator!=(const ConstIter & rhs) const
    {
      return node_ != rhs.node_;
    }

  private:
    friend AVLTree< Key, Value, Comparator >;
    const detail::TNode< Key, Value > * node_;
    explicit ConstIterator(const detail::TNode< Key, Value > * node):
      node_(node)
    {}

    tnode * min_elem(tnode * root) const
    {
      if (root == nullptr || root->left == nullptr)
      {
        return root;
      }
      return min_elem(root->left);
    }
  };
}

#endif
