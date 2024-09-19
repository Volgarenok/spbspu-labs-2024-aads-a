#ifndef CONSTLNRITER_HPP
#define CONSTLNRITER_HPP

#include <stack.hpp>

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class ConstRNLIter;

  template < class Key, class Value, class Compare >
  class ConstLNRIter: std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
  {
    using this_t = ConstLNRIter< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;

   public:
    ConstLNRIter() = default;

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const this_t & rhs) const noexcept;
    bool operator!=(const this_t & rhs) const noexcept;

    const std::pair< Key, Value > & operator*() const;
    const std::pair< Key, Value > * operator->() const;

   private:
    const node_t * current_;
    Stack< const node_t * > stack_;

    friend class BSTree< Key, Value, Compare >;
    friend class ConstRNLIter< Key, Value, Compare >;

    ConstLNRIter(const node_t * node, Stack< const node_t * > && s);
  };

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare >::ConstLNRIter(const node_t * node, Stack< const node_t * > && s):
   current_(node),
   stack_(s)
  {}

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare > & ConstLNRIter< Key, Value, Compare >::operator++()
  {
    if (!current_)
    {
      return *this;
    }
    if (current_->right)
    {
      stack_.push(current_);
      current_ = current_->right;
      while (current_->left)
      {
        stack_.push(current_);
        current_ = current_->left;
      }
    }
    else
    {
      while (!stack_.empty() && stack_.top()->right == current_)
      {
        current_ = stack_.top();
        stack_.pop();
        if (stack_.empty())
        {
          current_ = nullptr;
        }
      }
      if (!stack_.empty() && stack_.top()->left == current_)
      {
        current_ = stack_.top();
        stack_.pop();
      }
    }
    return *this;
  }

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare > ConstLNRIter< Key, Value, Compare >::operator++(int)
  {
    auto current = *this;
    ++(*this);
    return current;
  }

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare > & ConstLNRIter< Key, Value, Compare >::operator--()
  {
    if (!current_)
    {
      return *this;
    }
    if (current_->left)
    {
      stack_.push(current_);
      current_ = current_->left;
      while (current_->right)
      {
        stack_.push(current_);
        current_ = current_->right;
      }
    }
    else
    {
      while (!stack_.empty() && stack_.top()->left == current_)
      {
        current_ = stack_.top();
        stack_.pop();
        if (stack_.empty())
        {
          current_ = nullptr;
        }
      }
      if (!stack_.empty() && stack_.top()->right == current_)
      {
        current_ = stack_.top();
        stack_.pop();
      }
    }
    return *this;
  }

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare > ConstLNRIter< Key, Value, Compare >::operator--(int)
  {
    auto current = *this;
    --(*this);
    return current;
  }

  template < class Key, class Value, class Compare >
  bool ConstLNRIter< Key, Value, Compare >::operator==(const this_t & rhs) const noexcept
  {
    return current_ == rhs.current_;
  }

  template < class Key, class Value, class Compare >
  bool ConstLNRIter< Key, Value, Compare >::operator!=(const this_t & rhs) const noexcept
  {
    return current_ != rhs.current_;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > & ConstLNRIter< Key, Value, Compare >::operator*() const
  {
    return current_->data;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > * ConstLNRIter< Key, Value, Compare >::operator->() const
  {
    return std::addressof(current_->data);
  }
}

#endif
