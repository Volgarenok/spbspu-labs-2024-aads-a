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
    RedBlackTree();
    ~RedBlackTree();
    void clear();
    std::pair< iterator, bool > insert(const T & value);
  private:
    using node = detail::Node< Key, T >;
    node * last_;
    node * root_;
    char fake_[sizeof(node)];
    node * createFakeLeaf();
    void clear_subtree(node * subtree);
  };

  template< class Key, class T, class Compare >
  detail::Node< Key, T > * RedBlackTree< Key, T, Compare >::createFakeLeaf()
  {
    return reinterpret_cast< node * >(fake_);
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
  void RedBlackTree< Key, T, Compare >::clear_subtree(node * subtree)
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
  void RedBlackTree< Key, T, Compare >::clear()
  {
    clear_subtree(root_);
  }
}

#endif
