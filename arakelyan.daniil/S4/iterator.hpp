#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <functional>
#include <memory>

#include "node.hpp"

namespace arakelyan
{
  template < class Key, class Value, class Comparator >
  struct RBTree;

  template < class Key, class Value, class Comparator >
  struct Iterator
  {
  public:
    friend struct RBTree< Key, Value, Comparator >;
    using value_t = std::pair< Key, Value >;

    Iterator();
    Iterator(const Iterator &val) = default;
    ~Iterator() = default;
    Iterator &operator=(const Iterator &val) = default;

    Iterator &operator++();
    Iterator operator++(int);

    Iterator &operator--();
    Iterator operator--(int);

    const value_t &operator*() const;
    const value_t *operator->() const;
    value_t &operator*();
    value_t *operator->();

    bool operator!=(Iterator otherI) const;
    bool operator==(Iterator otherI) const;

  private:
    explicit Iterator(detail::Node< Key, Value > *val);

    void next()
    {
      detail::Node< Key, Value > *temp = node_;
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
          detail::Node< Key, Value > *parent = temp->parent_;
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
      detail::Node< Key, Value > *temp = node_;
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
          detail::Node< Key, Value > *parent = temp->parent_;
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

    detail::Node< Key, Value > *node_;
  };

  template < class Key, class Value, class Comparator >
  Iterator< Key, Value, Comparator >::Iterator():
    node_(nullptr)
  {}

  template < class Key, class Value, class Comparator >
  Iterator< Key, Value, Comparator >::Iterator(detail::Node< Key, Value > *root):
    node_(root)
  {
    while (node_ && node_->left_)
    {
      node_ = node_->left_;
    }
  }

  template < class Key, class Value, class Comparator >
  Iterator< Key, Value, Comparator > &Iterator< Key, Value, Comparator >::operator++()
  {
    assert(node_ != nullptr);
    next();
    return *this;
  }

  template < class Key, class Value, class Comparator >
  Iterator< Key, Value, Comparator > Iterator< Key, Value, Comparator >::operator++(int)
  {
    assert(node_ != nullptr);
    Iterator res(*this);
    next();
    return res;
  }

  template < class Key, class Value, class Comparator >
  Iterator< Key, Value, Comparator > &Iterator< Key, Value, Comparator >::operator--()
  {
    assert(node_ != nullptr);
    prev();
    return *this;
  }

  template < class Key, class Value, class Comparator >
  Iterator< Key, Value, Comparator > Iterator< Key, Value, Comparator >::operator--(int)
  {
    assert(node_ != nullptr);
    Iterator res(*this);
    prev();
    return res;
  }

  template < class Key, class Value, class Comparator >
  const std::pair< Key, Value > &Iterator< Key, Value, Comparator >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template < class Key, class Value, class Comparator >
  const std::pair< Key, Value > *Iterator< Key, Value, Comparator >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template < class Key, class Value, class Comparator >
  std::pair< Key, Value > &Iterator< Key, Value, Comparator >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template < class Key, class Value, class Comparator >
  std::pair< Key, Value > *Iterator< Key, Value, Comparator >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template < class Key, class Value, class Comparator >
  bool Iterator< Key, Value, Comparator >::operator!=(Iterator< Key, Value, Comparator > otherI) const
  {
    return !(*this == otherI);
  }

  template < class Key, class Value, class Comparator >
  bool Iterator< Key, Value, Comparator >::operator==(Iterator< Key, Value, Comparator > otherI) const
  {
    return node_ == otherI.node_;
  }
}
#endif
