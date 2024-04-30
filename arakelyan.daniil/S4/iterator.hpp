#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <stack>

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

    Iterator &operator++();//fine
    Iterator operator++(int);//fine

    Iterator &operator--();//fine
    Iterator operator--(int);//fine

    const T &operator*() const;//fine
    T &operator*();//fine
    const T *operator->() const;//fine
    T *operator->();//fine

    bool operator!=(Iterator< T > val) const;//fine
    bool operator==(Iterator< T > val) const;//fine

  private:
    explicit Iterator(detail::Node< T > *val);

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
          while (parent && node_ == node_->right_)
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
  T &Iterator< T >::operator*()
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
  T *Iterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template < class T >
  bool Iterator< T >::operator!=(Iterator< T > val) const
  {
    return !(*this == val);
  }

  template < class T >
  bool Iterator< T >::operator==(Iterator< T > val) const
  {
    return node_ == val.node_;
  }
}
#endif
