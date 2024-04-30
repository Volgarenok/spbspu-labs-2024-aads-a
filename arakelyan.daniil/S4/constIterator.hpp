#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <cassert>
#include <memory>

#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct RBTree;

  template < class T >
  struct ConstIterator
  {
  public:
    friend struct RBTree< T >;

    ConstIterator();
    ConstIterator(const ConstIterator< T > &val) = default;
    ~ConstIterator() = default;
    ConstIterator &operator=(const ConstIterator< T > &val) = default;

    ConstIterator &operator++();
    ConstIterator operator++(int);

    ConstIterator &operator--();
    ConstIterator operator--(int);

    const T &operator*() const;
    const T *operator->() const;

    bool operator!=(ConstIterator< T > otherI) const;
    bool operator==(ConstIterator< T > otherI) const;

  private:
    explicit ConstIterator(detail::Node< T > *sNode);

  void next()
  {
    if (node_)
    {
      if (node_->right_)
      {
        node_ = node_->right_;
        while (node_->left_)
        {
          node_ = node_->left_;
        }
      }
      else
      {
        detail::Node<T> *parent = node_->parent_;
        while (parent && node_ == parent->right_)
        {
          node_ = parent;
          parent = parent->parent_;
        }
        node_ = parent;
      }
    }
  }

    void prev()
    {
      detail::Node<T> *temp = node_;

      if (temp->left_)
      {
        temp = temp->left_;
        while (temp->right_)
        {
          temp = temp->right_;
        }
      }
      else
      {
        detail::Node<T> *parent = temp->parent_;
        while (parent && temp == parent->left_)
        {
          temp = parent;
          parent = parent->parent_;
        }
        temp = parent;
      }
      node_ = temp;
    }

    detail::Node< T > *node_;
  };

  template < class T >
  ConstIterator< T >::ConstIterator():
    node_(nullptr)
  {}

  template < class T >
  ConstIterator< T >::ConstIterator(detail::Node< T > *sNode):
    node_(sNode)
  {
    while (node_ && node_->left_)
    {
      node_ = node_->left_;
    }
  }

  template < class T >
  ConstIterator< T > &ConstIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    next();
    return *this;
  }

  template < class T >
  ConstIterator< T > ConstIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    ConstIterator res(*this);
    next();
    return res;
  }

  template < class T >
  ConstIterator< T > &ConstIterator< T >::operator--()
  {
    assert(node_ != nullptr);
    prev();
    return *this;
  }

  template < class T >
  ConstIterator< T > ConstIterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    ConstIterator res(*this);
    prev();
    return res;
  }

  template < class T >
  const T &ConstIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template < class T >
  const T *ConstIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template < class T >
  bool ConstIterator< T >::operator==(ConstIterator< T > otherI) const
  {
    return node_ == otherI.node_;
  }

  template < class T >
  bool ConstIterator< T >::operator!=(ConstIterator< T > otherI) const
  {
    return !(*this == otherI);
  }
}
#endif
