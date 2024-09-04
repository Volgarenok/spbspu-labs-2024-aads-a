#ifndef CONSTTREEITER_HPP
#define CONSTTREEITER_HPP

#include <iterator>
#include "treeNode.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class ConstLNRIter;

  template < class Key, class Value, class Compare >
  class ConstRNLIter;

  template < class Key, class Value, class Compare >
  class ConstTreeIter: public std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
  {
    using this_t = ConstTreeIter< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;
    using const_lnr_iterator = ConstLNRIter< Key, Value, Compare >;
    using const_rnl_iterator = ConstRNLIter< Key, Value, Compare >;

   public:
    ConstTreeIter();
    ConstTreeIter(const const_lnr_iterator & rhs);
    ConstTreeIter(const const_rnl_iterator & rhs);
    this_t & operator=(const const_lnr_iterator & rhs);
    this_t & operator=(const const_rnl_iterator & rhs);

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const this_t & rhs);
    bool operator!=(const this_t & rhs);

    const std::pair< Key, Value > & operator*() const;
    const std::pair< Key, Value > * operator->() const;

   private:
    node_t * current_;
    friend class BSTree< Key, Value, Compare >;
    friend class ConstLNRIter< Key, Value, Compare >;
    friend class ConstRNLIter< Key, Value, Compare >;

    explicit ConstTreeIter(node_t * node);
  };

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare >::ConstTreeIter():
   current_(nullptr)
  {}

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare >::ConstTreeIter(const const_lnr_iterator & rhs):
   current_(rhs.current_)
  {}

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare >::ConstTreeIter(const const_rnl_iterator & rhs):
   current_(rhs.current_)
  {}

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > & ConstTreeIter< Key, Value, Compare >::operator=(const const_lnr_iterator & rhs)
  {
    current_ = rhs.current_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > & ConstTreeIter< Key, Value, Compare >::operator=(const const_rnl_iterator & rhs)
  {
    current_ = rhs.current_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare >::ConstTreeIter(node_t * node):
   current_(node)
  {}

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > & ConstTreeIter< Key, Value, Compare >::operator++()
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
  ConstTreeIter< Key, Value, Compare > ConstTreeIter< Key, Value, Compare >::operator++(int)
  {
    auto iter = *this;
    ++(*this);
    return iter;
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > & ConstTreeIter< Key, Value, Compare >::operator--()
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
  ConstTreeIter< Key, Value, Compare > ConstTreeIter< Key, Value, Compare >::operator--(int)
  {
    auto iter = *this;
    --(*this);
    return iter;
  }

  template < class Key, class Value, class Compare >
  bool ConstTreeIter< Key, Value, Compare >::operator==(const this_t & rhs)
  {
    return current_ == rhs.current_;
  }

  template < class Key, class Value, class Compare >
  bool ConstTreeIter< Key, Value, Compare >::operator!=(const this_t & rhs)
  {
    return !(*this == rhs);
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > & ConstTreeIter< Key, Value, Compare >::operator*() const
  {
    return current_->data;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > * ConstTreeIter< Key, Value, Compare >::operator->() const
  {
    return std::addressof(current_->data);
  }
}

#endif
