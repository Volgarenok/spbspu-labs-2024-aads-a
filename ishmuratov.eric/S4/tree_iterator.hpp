#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "comparator.hpp"
#include "tree.hpp"
#include "tree_node.hpp"
#include <memory>

namespace ishmuratov
{
  template< class Key, class Value, class Comparator >
  class AVLTree;

  template< class Key, class Value, class Comparator >
  class Iterator
  {
    using Iter = Iterator< Key, Value, Comparator >;
    using pair = std::pair< Key, Value >;
    using tnode = detail::TNode< Key, Value >;
  public:
    Iterator():
      node_(nullptr)
    {}

    ~Iterator() = default;
    Iterator(const Iter &) = default;
    Iter & operator=(const Iter &) = default;

    tnode * min_elem(tnode * root)
    {
      if (root == nullptr || root->left == nullptr)
      {
        return root;
      }
      return min_elem(root->left);
    }

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

    Iter operator++(int)
    {
      Iter result(*this);
      ++(*this);
      return result;
    }

//    Iter & operator--()
//    {
//      return *this;
//    }

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
  };
}

#endif