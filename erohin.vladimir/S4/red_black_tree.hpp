#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>
#include "tree_node.hpp"

namespace erohin
{
  template< class Key, class T, class Compare = std::less< Key > >
  class RedBlackTree
  {
  public:
    RedBlackTree();
    ~RedBlackTree();
    void clear();

  private:
    using Node = detail::TreeNode< Key, T >;

    Node * leaf_;
    Node * root_;
    char fake_[sizeof(Node)];
    Node * createFakeLeaf();
    void clear_subtree(Node * subtree);
  };

  template< class Key, class T, class Compare >
  detail::TreeNode< Key, T > * RedBlackTree< Key, T, Compare >::createFakeLeaf()
  {
    return reinterpret_cast< Node * >(fake_);
  }

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::RedBlackTree():
    leaf_(createFakeLeaf()),
    root_(leaf_)
  {}

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::~RedBlackTree()
  {
    clear();
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::clear_subtree(Node * subtree)
  {
    if (subtree == leaf_)
    {
      return;
    }
    else if (subtree->left_ == leaf_ && subtree->right_ == leaf_)
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
