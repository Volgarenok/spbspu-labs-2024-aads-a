#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>
#include <initializer_list>
#include "tree_node.hpp"
#include "tree_const_iterator.hpp"
#include "tree_iterator.hpp"

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
    std::pair< iterator, bool > insert(const value_type & value);
  private:
    detail::Node< Key, T > * last_;
    detail::Node< Key, T > * root_;
    char fake_[sizeof(detail::Node< Key, T >)];
    Compare cmp_;
    detail::Node< Key, T > * createFakeLeaf();
    void clear_subtree(detail::Node< Key, T > * subtree);
    bool is_leaf(detail::Node< Key, T > * node);
    bool is_last(detail::Node< Key, T > * node);
  };

  template< class Key, class T, class Compare >
  detail::Node< Key, T > * RedBlackTree< Key, T, Compare >::createFakeLeaf()
  {
    detail::Node< Key, T > * result = reinterpret_cast< detail::Node< Key, T > * >(fake_);
    result->left_ = nullptr;
    result->right_ = nullptr;
    return result;
  }

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::RedBlackTree():
    last_(createFakeLeaf()),
    root_(last_)
  {}

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::~RedBlackTree()
  {
    clear();
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::clear_subtree(detail::Node< Key, T > * subtree)
  {
    if (subtree == last_ || !subtree)
    {
      return;
    }
    else if (subtree->left_ == last_ && subtree->right_ == last_)
    {
      delete subtree;
      return;
    }
    clear_subtree(subtree->left_);
    clear_subtree(subtree->right_);
    delete subtree;
  }

  template< class Key, class T, class Compare >
  bool RedBlackTree< Key, T, Compare >::is_leaf(detail::Node< Key, T > * node)
  {
    return (node->left_ && node->right_);
  }

  template< class Key, class T, class Compare >
  bool RedBlackTree< Key, T, Compare >::is_last(detail::Node< Key, T > * node)
  {
    return (node->left_ == last_ || node->right_ == last_);
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::clear()
  {
    clear_subtree(root_);
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T >, bool > RedBlackTree< Key, T, Compare >::insert(const value_type & value)
  {
    detail::Node< Key, T > * node = root_;
    while (is_leaf(node) || is_last(node))
    {
      if (node->data_.first == value.first)
      {
        return std::make_pair(iterator(node), false);
      }
      else if (cmp_(node->data_.first, value.first))
      {
        node = node->left_;
      }
      else
      {
        node = node->right_;
      }
    }
    detail::Node< Key, T > * prev = node;
    node = new detail::Node< Key, T >(value, prev, prev->left_, prev->right_);
    if (cmp_(node->data_.first, prev->data_.first))
    {
      prev->left_ = node;
    }
    else
    {
      prev->right_ = node;
    }
    return std::make_pair(iterator(node), true);
  }
}

#endif
