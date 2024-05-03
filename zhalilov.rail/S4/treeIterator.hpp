#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP

#include <iterator>

#include "treeNode.hpp"

namespace zhalilov
{
  template < class Key, class T, class Compare >
  class TwoThreeTree;

  template < class T >
  class TwoThreeIterator: public std::iterator < std::bidirectional_iterator_tag, T >
  {
  public:
    ~TwoThreeIterator() = default;

    TwoThreeIterator &operator=(const TwoThreeIterator &) = default;

    TwoThreeIterator &operator++();
    TwoThreeIterator &operator--();
    TwoThreeIterator operator++(int);
    TwoThreeIterator operator--(int);

    T &operator*();
    T *operator->();
    const T &operator*() const;
    const T *operator->() const;

    bool operator==(const TwoThreeIterator &) const;
    bool operator!=(const TwoThreeIterator &) const;

    template < class Key, class Value, class Compare >
    friend class TwoThree;

  private:
    detail::TreeNode < T > *node_;
    bool isPtrToLeft_;

    explicit TwoThreeIterator(detail::TreeNode < T > *node, bool isPtrToLeft = true);
    static detail::TreeNode < T > *findMin(detail::TreeNode < T > *);
    static detail::TreeNode < T > *findMax(detail::TreeNode < T > *);
  };

  template < class T >
  TwoThreeIterator < T > &TwoThreeIterator < T >::operator++()
  {
    if (node_->type == detail::NodeType::Three)
    {
      if (isPtrToLeft_)
      {
        detail::TreeNode < T > *minMid = findMin(node_->mid);
        if (minMid == node_)
        {
          isPtrToLeft_ = false;
        }
        node_ = minMid;
        return *this;
      }
    }

    detail::TreeNode < T > *minRight = findMin(node_->right);
    if (minRight == node_)
    {
      while (node_->parent && node_->parent->right == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
    }
    else
    {
      node_ = minRight;
    }
    isPtrToLeft_ = true;
    return *this;
  }

  template < class T >
  TwoThreeIterator < T > &TwoThreeIterator < T >::operator--()
  {
    if (node_->type == detail::NodeType::Three)
    {
      if (!isPtrToLeft_)
      {
        detail::TreeNode < T > *maxMid = findMax(node_->mid);
        if (maxMid == node_)
        {
          isPtrToLeft_ = true;
        }
        node_ = maxMid;
        return *this;
      }
    }

    detail::TreeNode < T > *maxLeft = findMax(node_->left);
    if (maxLeft == node_)
    {
      while (node_->parent->left == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
    }
    else
    {
      node_ = maxLeft;
    }
    isPtrToLeft_ = false;
    return *this;
  }

  template < class T >
  TwoThreeIterator < T > TwoThreeIterator < T >::operator++(int)
  {
    TwoThreeIterator temp(*this);
    operator++();
    return temp;
  }

  template < class T >
  TwoThreeIterator < T > TwoThreeIterator < T >::operator--(int)
  {
    TwoThreeIterator temp(*this);
    operator--();
    return temp;
  }

  template < class T >
  T &TwoThreeIterator < T >::operator*()
  {
    if (node_->type == detail::NodeType::Three)
    {
      if (!isPtrToLeft_)
      {
        return node_->two;
      }
    }
    return node_->one;
  }

  template < class T >
  T *TwoThreeIterator < T >::operator->()
  {
    if (node_->type == detail::NodeType::Three)
    {
      if (!isPtrToLeft_)
      {
        return &node_->two;
      }
    }
    return &node_->one;
  }

  template < class T >
  const T &TwoThreeIterator < T >::operator*() const
  {
    return operator*();
  }

  template < class T >
  const T *TwoThreeIterator < T >::operator->() const
  {
    return operator->();
  }

  template < class T >
  bool TwoThreeIterator < T >::operator==(const TwoThreeIterator < T > &ait) const
  {
    bool isEqualValue = true;
    if (node_->type == detail::NodeType::Three)
    {
      isEqualValue = ait.isPtrToLeft_ == isPtrToLeft_;
    }
    return ait.node_ == node_ && isEqualValue;
  }

  template < class T >
  bool TwoThreeIterator < T >::operator!=(const TwoThreeIterator < T > &ait) const
  {
    return !operator==(ait);
  }

  template < class T >
  TwoThreeIterator < T >::TwoThreeIterator(detail::TreeNode < T > *node, bool isPtrToLeft):
    node_(node),
    isPtrToLeft_(isPtrToLeft)
  {}

  template < class T >
  detail::TreeNode < T > *TwoThreeIterator < T >::findMin(detail::TreeNode < T > *nodeFrom)
  {
    detail::TreeNode < T > *minNode = nodeFrom;
    while (minNode && minNode->left)
    {
      minNode = minNode->left;
    }
    return minNode;
  }

  template < class T >
  detail::TreeNode < T > *TwoThreeIterator < T >::findMax(detail::TreeNode < T > *nodeFrom)
  {
    detail::TreeNode < T > *maxNode = nodeFrom;
    while (maxNode && maxNode->right)
    {
      maxNode = maxNode->right;
    }
    return maxNode;
  }
}

#endif
