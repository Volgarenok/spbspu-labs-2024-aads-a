#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <cassert>
#include <functional>
#include <memory>

#include "node.hpp"

namespace arakelyan
{
  template < class Key, class Value, class Comparator >
  struct RBTree;

  template < class Key, class Value, class Comparator = std::less< Key > >
  struct ConstIterator
  {
  public:
    friend struct RBTree< Key, Value, Comparator >;
    using value_t = std::pair< Key, Value >;

    ConstIterator();
    ConstIterator(const ConstIterator &val) = default;
    ~ConstIterator() = default;
    ConstIterator &operator=(const ConstIterator &val) = default;

    ConstIterator &operator++();
    ConstIterator operator++(int);

    ConstIterator &operator--();
    ConstIterator operator--(int);

    const value_t &operator*() const;
    const value_t *operator->() const;

    bool operator!=(ConstIterator otherI) const;
    bool operator==(ConstIterator otherI) const;

  private:
    explicit ConstIterator(detail::Node< Key, Value > *sNode);

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
          detail::Node< Key, Value > *parent = node_->parent_;
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
      detail::Node< Key, Value > *temp = node_;

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

    detail::Node< Key, Value > *node_;
  };

  template < class Key, class Value, class Comparator >
  ConstIterator< Key, Value, Comparator >::ConstIterator():
    node_(nullptr)
  {}

  template < class Key, class Value, class Comparator  >
  ConstIterator< Key, Value, Comparator >::ConstIterator(detail::Node< Key, Value > *sNode):
    node_(sNode)
  {
    while (node_ && node_->left_)
    {
      node_ = node_->left_;
    }
  }

  template < class Key, class Value, class Comparator >
  ConstIterator< Key, Value, Comparator > &ConstIterator< Key, Value, Comparator >::operator++()
  {
    assert(node_ != nullptr);
    next();
    return *this;
  }

  template < class Key, class Value, class Comparator  >
  ConstIterator< Key, Value, Comparator > ConstIterator< Key, Value, Comparator >::operator++(int)
  {
    assert(node_ != nullptr);
    ConstIterator res(*this);
    next();
    return res;
  }

  template < class Key, class Value, class Comparator >
  ConstIterator< Key, Value, Comparator > &ConstIterator< Key, Value, Comparator >::operator--()
  {
    assert(node_ != nullptr);
    prev();
    return *this;
  }

  template < class Key, class Value, class Comparator >
  ConstIterator< Key, Value, Comparator > ConstIterator< Key, Value, Comparator >::operator--(int)
  {
    assert(node_ != nullptr);
    ConstIterator res(*this);
    prev();
    return res;
  }

  template < class Key, class Value, class Comparator >
  const std::pair< Key, Value > &ConstIterator< Key, Value, Comparator >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template < class Key, class Value, class Comparator >
  const std::pair< Key, Value > *ConstIterator< Key, Value, Comparator >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template < class Key, class Value, class Comparator >
  bool ConstIterator< Key, Value, Comparator >::operator==(ConstIterator< Key, Value, Comparator > otherI) const
  {
    return node_ == otherI.node_;
  }

  template < class Key, class Value, class Comparator >
  bool ConstIterator< Key, Value, Comparator >::operator!=(ConstIterator< Key, Value, Comparator > otherI) const
  {
    return !(*this == otherI);
  }
}
#endif
