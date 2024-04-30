#ifndef CONST_TREE_ITERATOR_HPP
#define CONST_TREE_ITERATOR_HPP

#include "tree_node.hpp"

namespace nikitov
{
  template< class Key, class T, class Compare >
  class Tree;

  template< class Key, class T, class Compare = std::less< Key > >
  class ConstTreeIterator
  {
    friend class Tree< Key, T, Compare >;
  public:
    explicit ConstTreeIterator(detail::TreeNode< Key, T, Compare >* node);
    ~ConstTreeIterator() = default;

    ConstTreeIterator< Key, T, Compare >& operator++();

  private:
    bool isFirst_;
    detail::TreeNode< Key, T, Compare >* node_;

    void fallLeft();
  };

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >::ConstTreeIterator(detail::TreeNode< Key, T, Compare >* node):
    isFirst_(true),
    node_(node)
  {}

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >& ConstTreeIterator< Key, T, Compare >::operator++()
  {
    if (isFirst_)
    {
      if (node_->size_ == 2)
      {
        if (node_->middle_)
        {
          node_ = node_->middle_;
          fallLeft();
        }
        else
        {
          isFirst_ == false;
        }
      }
      else
      {
        if (node_->right_)
        {
          node_ = node_->right_;
          fallLeft();
        }
        else
        {
          if (node_->parent_->right_ == node_)
          {
            while (node_->parent_->parent_)
            {
              node_ = node_->parent_;
            }
          }
          else
          {
            while (node_->parent_)
            {
              node_ = node_->parent_;
            }
          }
        }
      }
    }
    else
    {
      if (node_->right_)
      {
        node_ = node_->right_;
        fallLeft();
      }
      else
      {
        if (node_->parent_->right_ == node_)
        {
          while (node_->parent_->parent_)
          {
            node_ = node_->parent_;
          }
        }
        else
        {
          while (node_->parent_)
          {
            node_ = node_->parent_;
          }
        }
      }
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  void ConstTreeIterator< Key, T, Compare >::fallLeft()
  {
    while (node_->left_)
    {
      node_ = node_->left_;
    }
    isFirst_ = true;
  }
}
#endif
