#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <memory>

#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct RBTree;

  template < class T >
  struct Iterator
  {
  public:
    friend struct RBTree< T >;

    Iterator();
    Iterator(const Iterator< T > &val) = default;
    ~Iterator() = default;
    Iterator &operator=(const Iterator< T > &val) = default;

    Iterator &operator++();
    Iterator operator++(int);

    Iterator &operator--();
    Iterator operator--(int);

    const T &operator*() const;
    const T *operator->() const;
    T &operator*();
    T *operator->();

    bool operator!=(Iterator< T > otherI) const;
    bool operator==(Iterator< T > otherI) const;

  private:
    explicit Iterator(detail::Node< T > *val);

    void next()
    {
      detail::Node< T > *temp = node_;
      if (temp)
      {
        if (temp->right_)
        {
          temp = temp->right_;
          while (temp->left_)
          {
            temp = temp->left_;
          }
        }
        else
        {
          detail::Node< T > *parent = temp->parent_;
          while (parent && temp == parent->right_)
          {
            temp = parent;
            parent = parent->parent_;
          }
          temp = parent;
        }
        node_ = temp;
      }
    }

    void prev()
    {
      detail::Node< T > *temp = node_;
      if (temp)
      {
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
          detail::Node< T > *parent = temp->parent_;
          while (parent && temp == parent->left_)
          {
            temp = parent;
            parent = parent->parent_;
          }
          temp = parent;
        }
        node_ = temp;
      }
    }

    detail::Node< T > *node_;
  };

  template < class T >
  Iterator< T >::Iterator():
    node_(nullptr)
  {}

  template < class T >
  Iterator< T >::Iterator(detail::Node< T > *root):
    node_(root)
  {
    while (node_ && node_->left_)
    {
      node_ = node_->left_;
    }
  }

  template < class T >
  Iterator< T > &Iterator< T >::operator++()
  {
    assert(node_ != nullptr);
    next();
    return *this;
  }

  template < class T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    Iterator res(*this);
    next();
    return res;
  }

  template < class T >
  Iterator< T > &Iterator< T >::operator--()
  {
    assert(node_ != nullptr);
    prev();
    return *this;
  }

  template < class T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    Iterator res(*this);
    prev();
    return res;
  }

  template < class T >
  const T &Iterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template < class T >
  const T *Iterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template < class T >
  T &Iterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template < class T >
  T *Iterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template < class T >
  bool Iterator< T >::operator!=(Iterator< T > otherI) const
  {
    return !(*this == otherI);
  }

  template < class T >
  bool Iterator< T >::operator==(Iterator< T > otherI) const
  {
    return node_ == otherI.node_;
  }
}
#endif
