#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>
#include <initializer_list>
#include "tree_node.hpp"
#include "tree_const_iterator.hpp"
#include "tree_iterator.hpp"

#include <iostream>

namespace erohin
{
  template< class Key, class T, class Compare = std::less< Key > >
  class RedBlackTree
  {
  public:
    using iterator = TreeIterator< Key, T >;
    using const_iterator = TreeConstIterator< Key, T >;
    using value_type = std::pair< Key, T >;
    RedBlackTree();
    ~RedBlackTree();
    void clear();
    bool empty() const noexcept;
    std::pair< iterator, bool > insert(const value_type & value);
  private:
    detail::Node< Key, T > * root_;
    Compare cmp_;
    void clear_subtree(detail::Node< Key, T > * subtree);
  };

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::RedBlackTree():
    root_(nullptr)
  {}

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::~RedBlackTree()
  {
    clear();
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::clear_subtree(detail::Node< Key, T > * subtree)
  {
    if (!subtree)
    {
      delete subtree;
      return;
    }
    clear_subtree(subtree->left_);
    clear_subtree(subtree->right_);
    delete subtree;
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::clear()
  {
    clear_subtree(root_);
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T >, bool > RedBlackTree< Key, T, Compare >::insert(const value_type & value)
  {
    if (empty())
    {
      root_ = new detail::Node< Key, T >(value, nullptr, nullptr, nullptr);
      return std::make_pair(iterator(root_), true);
    }
    detail::Node< Key, T > * node = root_;
    detail::Node< Key, T > * prev = node;
    while (node)
    {
      prev = node;
      if (node->data_.first == value.first)
      {
        return std::make_pair(iterator(node), false);
      }
      else if (cmp_(value.first, node->data_.first))
      {
        std::cout << node->data_.first << " : " << value.first << "\n";
        node = node->left_;
      }
      else
      {
        node = node->right_;
      }
    }
    node = new detail::Node< Key, T >(value, prev, prev->left_, prev->right_);
    if (cmp_(node->data_.first, prev->data_.first))
    {
      prev->left_ = node;
    }
    else
    {
      prev->right_ = node;
    }
    std::cout << node << " " << node->parent_ << " " << node->left_ << " " << node->right_ << "\n";
    return std::make_pair(iterator(node), true);
  }

  template< class Key, class T, class Compare >
  bool RedBlackTree< Key, T, Compare >::empty() const noexcept
  {
    return (!root_);
  }
}

#endif
