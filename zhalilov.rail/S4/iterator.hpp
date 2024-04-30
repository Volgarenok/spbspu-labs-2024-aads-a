#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

#include "node.hpp"

namespace zhalilov
{
  template < class Key, class T, class Compare >
  class TwoThreeTree < Key, T, Compare >;

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

    bool operator==(const TwoThreeIterator < T > &) const;
    bool operator!=(const TwoThreeIterator < T > &) const;

    template < class Key, class Value, class Compare >
    friend TwoThreeTree < Key, Value, Compare >;

  private:
    detail::Node < T > *node_;
    bool isPtrToLeft_;

    explicit TwoThreeIterator(detail::Node < T > *node, bool isPtrToLeft = true);
    detail::Node < T > *findMin(const detail::Node < T > *);
    detail::Node < T > *findMax(const detail::Node < T > *);
  };

  template < class T >
  TwoThreeIterator < T > &TwoThreeIterator < T >::operator++()
  {
    if (node_->type == detail::NodeType::Three)
    {
      if (isPtrToLeft_)
      {
        detail::Node < T > *minMid = findMin(node_->mid);
        if (minMid == node_)
        {
          isPtrToLeft_ = false;
        }
        node_ = minMid;
        return *this;
      }
    }

    detail::Node < T > *minRight = findMin(node_->right);
    if (minRight == node_)
    {
      while (node_->parent->right == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
      isPtrToLeft_ = true;
    }
    else
    {
      node_ = minRight;
    }
    return *this;
  }

  template < class T >
  TwoThreeIterator < T > &TwoThreeIterator < T >::operator--()
  {
    if (node_->type == detail::NodeType::Three)
    {
      if (!isPtrToLeft_)
      {
        detail::Node < T > *maxMid = findMax(node_->mid);
        if (maxMid == node_)
        {
          isPtrToLeft_ = false;
        }
        return *this;
      }
    }

    detail::Node < T > *maxLeft = findMax(node_->left);
    if (maxLeft == node_)
    {
      while (node_->parent->left == node_)
      {
        node_ = node_->parent;
      }
      isPtrToLeft_ = false;
    }
    else
    {
      node_ = maxLeft;
    }
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
        return node_->two;
      }
    }
    return *node_->one;
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
  TwoThreeIterator < T >::TwoThreeIterator(detail::Node < T > *node, bool isPtrToLeft):
    node_(node),
    isPtrToLeft_(isPtrToLeft)
  {}

  template < class T >
  detail::Node < T > *TwoThreeIterator < T >::findMin(const detail::Node < T > *nodeFrom)
  {
    detail::Node < T > *minNode = nodeFrom;
    while (minNode->left)
    {
      minNode = minNode->left;
    }
    return minNode;
  }

  template < class T >
  detail::Node < T > *TwoThreeIterator < T >::findMax(const detail::Node < T > *nodeFrom)
  {
    detail::Node < T > *maxNode = nodeFrom;
    while (maxNode->right)
    {
      maxNode = maxNode->right;
    }
    return maxNode;
  }
}

#endif
