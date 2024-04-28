#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "tree_node.hpp"

namespace erohin
{
  template< class T >
  class RedBlackTree
  {
  public:
    RedBlackTree();
    ~RedBlackTree();
    void clear();

  private:
    using Node = detail::TreeNode< T >;

    Node * leaf_;
    Node * root_;
    char fake_[sizeof(Node)];
    Node * createFakeLeaf();
    void clear_subtree(Node * subtree);
  };

  template< class T >
  detail::TreeNode< T > * RedBlackTree< T >::createFakeLeaf()
  {
    return reinterpret_cast< Node * >(fake_);
  }

  template< class T >
  RedBlackTree< T >::RedBlackTree():
    leaf_(createFakeLeaf()),
    root_(leaf_)
  {}

  template< class T >
  RedBlackTree< T >::~RedBlackTree()
  {
    clear();
  }

  template< class T >
  void RedBlackTree< T >::clear_subtree(Node * subtree)
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

  template< class T >
  void RedBlackTree< T >::clear()
  {
    clear_subtree(root_);
  }
}

#endif
