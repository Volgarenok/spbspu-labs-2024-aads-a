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

    const std::pair< Key, T >& operator*() const;
    const std::pair< Key, T >* operator->() const;

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
  const std::pair< Key, T >& ConstTreeIterator< Key, T, Compare >::operator*() const
  {
    if (isFirst_)
    {
      return node_->firstValue_;
    }
    else
    {
      return node_->secondValue_;
    }
  }

  template< class Key, class T, class Compare >
  const std::pair< Key, T >* ConstTreeIterator< Key, T, Compare >::operator->() const
  {
    if (isFirst_)
    {
      return std::addressof(node_->firstValue_);
    }
    else
    {
      return std::addressof(node_->secondValue_);
    }
  }

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
          isFirst_ = false;
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
            while (node_->parent_->right_ == node_)
            {
              node_ = node_->parent_;
            }
            if (!node_->parent_->parent_)
            {
              node_ = node_->parent_;
            }
          }
          else if (node_->parent_->middle_ == node_)
          {
            node_ = node_->parent_;
            isFirst_ = false;
          }
          else
          {
            node_ = node_->parent_;
            isFirst_ = true;
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
          while (node_->parent_->right_ == node_)
          {
            node_ = node_->parent_;
          }
          if (!node_->parent_->parent_)
          {
            node_ = node_->parent_;
          }
        }
        else if (node_->parent_->middle_ == node_)
        {
          node_ = node_->parent_;
          isFirst_ = false;
        }
        else
        {
          node_ = node_->parent_;
          isFirst_ = true;
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
