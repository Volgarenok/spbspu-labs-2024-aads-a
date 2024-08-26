#ifndef CONST_TREEITERATOR_HPP
#define CONST_TREEITERATOR_HPP

#include <iterator>

#include "treeNode.hpp"

namespace zhalilov
{
  template < class Key, class T, class Compare >
  class TwoThree;

  template < class T >
  class ConstTwoThreeIterator: public std::iterator < std::bidirectional_iterator_tag, const T >
  {
  public:
    ~ConstTwoThreeIterator() = default;

    ConstTwoThreeIterator &operator=(const ConstTwoThreeIterator &) = default;

    ConstTwoThreeIterator &operator++();
    ConstTwoThreeIterator &operator--();
    ConstTwoThreeIterator operator++(int);
    ConstTwoThreeIterator operator--(int);

    const T &operator*() const;
    const T *operator->() const;

    bool operator==(ConstTwoThreeIterator) const;
    bool operator!=(ConstTwoThreeIterator) const;

    template < class Key, class Value, class Compare >
    friend class TwoThree;

  private:
    detail::TreeNode < T > *node_;
    bool isPtrToLeft_;

    explicit ConstTwoThreeIterator(detail::TreeNode < T > *node, bool isPtrToLeft = true);
    static detail::TreeNode < T > *findDeepestLeft(detail::TreeNode < T > *);
    static detail::TreeNode < T > *findDeepestRight(detail::TreeNode < T > *);
  };

  template < class T >
  ConstTwoThreeIterator < T > &ConstTwoThreeIterator < T >::operator++()
  {
    if (node_->type == detail::NodeType::Three)
    {
      if (isPtrToLeft_)
      {
        detail::TreeNode < T > *minMid = findDeepestLeft(node_->mid);
        if (minMid)
        {
          node_ = minMid;
        }
        else
        {
          isPtrToLeft_ = false;
        }
        return *this;
      }
    }

    detail::TreeNode < T > *minRight = findDeepestLeft(node_->right);
    if (!minRight)
    {
      if (node_ != node_->parent)
      {
        detail::TreeNode < T > *prevNode = node_;
        node_ = node_->parent;
        while (node_->right == prevNode)
        {
          prevNode = node_;
          node_ = node_->parent;
        }
      }
    }
    else
    {
      node_ = minRight;
    }
    isPtrToLeft_ = true;
    return *this;
  }

  template < class T >
  ConstTwoThreeIterator < T > &ConstTwoThreeIterator < T >::operator--()
  {
    if (node_->type == detail::NodeType::Three)
    {
      if (!isPtrToLeft_)
      {
        detail::TreeNode < T > *maxMid = findDeepestRight(node_->mid);
        if (maxMid == node_)
        {
          isPtrToLeft_ = true;
        }
        node_ = maxMid;
        return *this;
      }
    }

    detail::TreeNode < T > *maxLeft = findDeepestRight(node_->left);
    if (!maxLeft)
    {
      if (node_ != node_->parent)
      {
        while (node_->parent && node_->parent->left == node_)
        {
          node_ = node_->parent;
        }
        if (node_->parent)
        {
          node_ = node_->parent;
        }
      }
    }
    else
    {
      node_ = maxLeft;
    }
    isPtrToLeft_ = false;
    return *this;
  }

  template < class T >
  ConstTwoThreeIterator < T > ConstTwoThreeIterator < T >::operator++(int)
  {
    ConstTwoThreeIterator temp(*this);
    operator++();
    return temp;
  }

  template < class T >
  ConstTwoThreeIterator < T > ConstTwoThreeIterator < T >::operator--(int)
  {
    ConstTwoThreeIterator temp(*this);
    operator--();
    return temp;
  }

  template < class T >
  const T &ConstTwoThreeIterator < T >::operator*() const
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
  const T *ConstTwoThreeIterator < T >::operator->() const
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
  bool ConstTwoThreeIterator < T >::operator==(ConstTwoThreeIterator ait) const
  {
    if (node_->type == detail::NodeType::Three)
    {
      return ait.isPtrToLeft_ == isPtrToLeft_ && ait.node_ == node_;
    }
    return ait.node_ == node_;
  }

  template < class T >
  bool ConstTwoThreeIterator < T >::operator!=(ConstTwoThreeIterator ait) const
  {
    return !operator==(ait);
  }

  template < class T >
  ConstTwoThreeIterator < T >::ConstTwoThreeIterator(detail::TreeNode < T > *node, bool isPtrToLeft):
    node_(node),
    isPtrToLeft_(isPtrToLeft)
  {}

  template < class T >
  detail::TreeNode < T > *ConstTwoThreeIterator < T >::findDeepestLeft(detail::TreeNode < T > *nodeFrom)
  {
    detail::TreeNode < T > *minNode = nodeFrom;
    while (minNode && minNode->left && minNode->left != minNode)
    {
      minNode = minNode->left;
    }
    return minNode;
  }

  template < class T >
  detail::TreeNode < T > *ConstTwoThreeIterator < T >::findDeepestRight(detail::TreeNode < T > *nodeFrom)
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
