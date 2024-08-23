#ifndef CONST_TREE_ITERATOR_HPP
#define CONST_TREE_ITERATOR_HPP

#include <iterator>
#include <cassert>
#include "tree_node.hpp"

namespace nikitov
{
  template< class Key, class T, class Compare >
  class Tree;

  template< class Key, class T, class Compare >
  class LNRIterator;

  template< class Key, class T, class Compare >
  class RNLIterator;

  template< class Key, class T, class Compare >
  class BreadthIterator;

  template< class Key, class T, class Compare = std::less< Key > >
  class ConstTreeIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
  public:
    ConstTreeIterator(const ConstTreeIterator< Key, T, Compare >&) = default;
    ConstTreeIterator(const LNRIterator< Key, T, Compare >& other);
    ConstTreeIterator(const RNLIterator< Key, T, Compare >& other);
    ConstTreeIterator(const BreadthIterator< Key, T, Compare >& other);
    ~ConstTreeIterator() = default;

    ConstTreeIterator< Key, T, Compare >& operator=(const ConstTreeIterator< Key, T, Compare >&) = default;
    ConstTreeIterator< Key, T, Compare >& operator=(const LNRIterator< Key, T, Compare >& other);
    ConstTreeIterator< Key, T, Compare >& operator=(const RNLIterator< Key, T, Compare >& other);
    ConstTreeIterator< Key, T, Compare >& operator=(const BreadthIterator< Key, T, Compare >& other);

    ConstTreeIterator< Key, T, Compare >& operator++();
    ConstTreeIterator< Key, T, Compare > operator++(int);
    ConstTreeIterator< Key, T, Compare >& operator--();
    ConstTreeIterator< Key, T, Compare > operator--(int);

    const std::pair< Key, T >& operator*() const;
    const std::pair< Key, T >* operator->() const;

    bool operator==(const ConstTreeIterator< Key, T, Compare >& other) const;
    bool operator!=(const ConstTreeIterator< Key, T, Compare >& other) const;

  private:
    detail::TreeNode< Key, T, Compare >* node_;
    bool isFirst_;

    explicit ConstTreeIterator(detail::TreeNode< Key, T, Compare >* node, bool isFirst = true);

    void fallLeft();
    void fallRight();
  };

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >::ConstTreeIterator(detail::TreeNode< Key, T, Compare >* node, bool isFirst):
    node_(node),
    isFirst_(isFirst)
  {}

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >::ConstTreeIterator(const LNRIterator< Key, T, Compare >& other):
    node_(other.data_.top()),
    isFirst_(other.isFirst_)
  {}

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >::ConstTreeIterator(const RNLIterator< Key, T, Compare >& other):
    node_(other.iterator_.data_.top()),
    isFirst_(other.isFirst_)
  {}

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >::ConstTreeIterator(const BreadthIterator< Key, T, Compare >& other):
    node_(other.queue_.top()),
    isFirst_(other.isFirst_)
  {}

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >& ConstTreeIterator< Key, T, Compare >::operator=(const LNRIterator< Key, T, Compare >& other)
  {
    node_ = other.data_.top();
    isFirst_ = other.isFirst_;
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >& ConstTreeIterator< Key, T, Compare >::operator=(const RNLIterator< Key, T, Compare >& other)
  {
    node_ = other.iterator_.data_.top();
    isFirst_ = other.isFirst_;
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >& ConstTreeIterator< Key, T, Compare >::operator=(const BreadthIterator< Key, T, Compare >& other)
  {
    node_ = other.queue_.top();
    isFirst_ = other.isFirst_;
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >& ConstTreeIterator< Key, T, Compare >::operator++()
  {
    assert(node_->parent_);
    if (node_->size_ == 1 || !isFirst_)
    {
      if (node_->right_)
      {
        node_ = node_->right_;
        fallLeft();
      }
      else
      {
        isFirst_ = true;
        while (node_->parent_->right_ == node_)
        {
          node_ = node_->parent_;
        }
        if (node_->parent_->middle_ == node_ && node_->parent_->parent_)
        {
          isFirst_ = false;
        }
        node_ = node_->parent_;
      }
    }
    else
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
    return *this;
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare > ConstTreeIterator< Key, T, Compare >::operator++(int)
  {
    ConstTreeIterator< Key, T, Compare > temp(*this);
    ++*this;
    return temp;
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >& ConstTreeIterator< Key, T, Compare >::operator--()
  {
    if (!node_->parent_)
    {
      node_ = node_->middle_;
      fallRight();
    }
    else if (node_->size_ == 1 || isFirst_)
    {
      if (node_->left_)
      {
        node_ = node_->left_;
        fallRight();
      }
      else
      {
        isFirst_ = true;
        while (node_->parent_->left_ == node_)
        {
          node_ = node_->parent_;
        }
        if (node_->parent_->size_ == 2)
        {
          isFirst_ = false;
        }
        if (node_->parent_->middle_ == node_)
        {
          isFirst_ = true;
        }
        node_ = node_->parent_;
      }
    }
    else
    {
      if (node_->middle_)
      {
        node_ = node_->middle_;
        fallRight();
      }
      else
      {
        isFirst_ = true;
      }
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare > ConstTreeIterator< Key, T, Compare >::operator--(int)
  {
    ConstTreeIterator< Key, T, Compare > temp(*this);
    --*this;
    return temp;
  }

  template< class Key, class T, class Compare >
  const std::pair< Key, T >& ConstTreeIterator< Key, T, Compare >::operator*() const
  {
    assert(node_->size_ != 0);
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
    assert(node_->size_ != 0);
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
  bool ConstTreeIterator< Key, T, Compare >::operator==(const ConstTreeIterator< Key, T, Compare >& other) const
  {
    return (node_ == other.node_) && (isFirst_ == other.isFirst_);
  }

  template< class Key, class T, class Compare >
  bool ConstTreeIterator< Key, T, Compare >::operator!=(const ConstTreeIterator< Key, T, Compare >& other) const
  {
    return (node_ != other.node_) || (isFirst_ != other.isFirst_);
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

  template< class Key, class T, class Compare >
  void ConstTreeIterator< Key, T, Compare >::fallRight()
  {
    while (node_->right_)
    {
      node_ = node_->right_;
    }
    if (node_->size_ == 2)
    {
      isFirst_ = false;
    }
    else
    {
      isFirst_ = true;
    }
  }
}
#endif
