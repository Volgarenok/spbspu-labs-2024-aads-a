#ifndef TREEITER_HPP
#define TREEITER_HPP

#include <iterator>
#include "treeNode.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class LNRIter;

  template < class Key, class Value, class Compare >
  class RNLIter;

  template < class Key, class Value, class Compare >
  class TreeIter: public std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
  {
    using this_t = TreeIter< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;
    using lnr_iterator = LNRIter< Key, Value, Compare >;
    using rnl_iterator = RNLIter< Key, Value, Compare >;

   public:
    TreeIter();
    TreeIter(const lnr_iterator & rhs);
    TreeIter(const rnl_iterator & rhs);
    this_t & operator=(const lnr_iterator & rhs);
    this_t & operator=(const rnl_iterator & rhs);

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const this_t & rhs);
    bool operator!=(const this_t & rhs);

    std::pair< Key, Value > & operator*();
    const std::pair< Key, Value > & operator*() const;
    std::pair< Key, Value > * operator->();
    const std::pair< Key, Value > * operator->() const;

   private:
    node_t * current_;
    friend class BSTree< Key, Value, Compare >;
    friend class LNRIter< Key, Value, Compare >;
    friend class RNLIter< Key, Value, Compare >;

    explicit TreeIter(node_t * node);
  };

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare >::TreeIter():
   current_(nullptr)
  {}

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare >::TreeIter(node_t * node):
   current_(node)
  {}

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare >::TreeIter(const lnr_iterator & rhs):
   current_(rhs.current_)
  {}

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare >::TreeIter(const rnl_iterator & rhs):
   current_(rhs.current_)
  {}

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > & TreeIter< Key, Value, Compare >::operator=(const lnr_iterator & rhs)
  {
    current_ = rhs.current_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > & TreeIter< Key, Value, Compare >::operator=(const rnl_iterator & rhs)
  {
    current_ = rhs.current_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > & TreeIter< Key, Value, Compare >::operator++()
  {
    if (!current_)
    {
      return *this;
    }
    else if (current_->right)
    {
      current_= detail::traverse_left(current_->right);
    }
    else
    {
      if (current_->parent)
      {
        while (current_->parent && current_ == current_->parent->right)
        {
          current_ = detail::go_up(current_);
        }
        current_ = detail::go_up(current_);
      }
      else
      {
        current_ = nullptr;
      }
    }
    return *this;
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > TreeIter< Key, Value, Compare >::operator++(int)
  {
    auto iter = *this;
    ++(*this);
    return iter;
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > & TreeIter< Key, Value, Compare >::operator--()
  {
    if (!current_)
    {
      return *this;
    }
    else if (current_->left)
    {
      current_= detail::traverse_right(current_->right);
    }
    else
    {
      if (current_->parent)
      {
        while (current_->parent && current_ == current_->parent->left)
        {
          current_ = detail::go_up(current_);
        }
        current_ = detail::go_up(current_);
      }
      else
      {
        current_ = nullptr;
      }
    }
    return *this;
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > TreeIter< Key, Value, Compare >::operator--(int)
  {
    auto iter = *this;
    --(*this);
    return iter;
  }

  template < class Key, class Value, class Compare >
  bool TreeIter< Key, Value, Compare >::operator==(const this_t & rhs)
  {
    return current_ == rhs.current_;
  }

  template < class Key, class Value, class Compare >
  bool TreeIter< Key, Value, Compare >::operator!=(const this_t & rhs)
  {
    return !(*this == rhs);
  }

  template < class Key, class Value, class Compare >
  std::pair< Key, Value > & TreeIter< Key, Value, Compare >::operator*()
  {
    return current_->data;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > & TreeIter< Key, Value, Compare >::operator*() const
  {
    return current_->data;
  }

  template < class Key, class Value, class Compare >
  std::pair< Key, Value > * TreeIter< Key, Value, Compare >::operator->()
  {
    return std::addressof(current_->data);
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > * TreeIter< Key, Value, Compare >::operator->() const
  {
    return std::addressof(current_->data);
  }
}

#endif
