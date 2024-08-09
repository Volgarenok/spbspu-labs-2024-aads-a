#ifndef RNLITER_HPP
#define RNLITER_HPP

#include <stack.hpp>

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class RNLIter: std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
  {
    using this_t = RNLIter< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;

   public:
    RNLIter() = default;

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const this_t & rhs) const noexcept;
    bool operator!=(const this_t & rhs) const noexcept;

    std::pair< Key, Value > & operator*();
    const std::pair< Key, Value > & operator*() const;
    std::pair< Key, Value > * operator->();
    const std::pair< Key, Value > * operator->() const;

   private:
    node_t * current_;
    Stack< node_t * > stack_;
    friend class BSTree< Key, Value, Compare >;

    RNLIter(node_t * node, Stack< node_t * > && s);
  };

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare >:: RNLIter(node_t * node, Stack< node_t * > && s):
   current_(node),
   stack_(s)
  {}

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare > & RNLIter< Key, Value, Compare >::operator++()
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
  RNLIter< Key, Value, Compare > RNLIter< Key, Value, Compare >::operator++(int)
  {
    auto current = *this;
    ++(*this);
    return current;
  }

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare > & RNLIter< Key, Value, Compare >::operator--()
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
  RNLIter< Key, Value, Compare > RNLIter< Key, Value, Compare >::operator--(int)
  {
    auto current = *this;
    --(*this);
    return current;
  }

  template < class Key, class Value, class Compare >
  bool RNLIter< Key, Value, Compare >::operator==(const this_t & rhs) const noexcept
  {
    return current_ == rhs.current_;
  }

  template < class Key, class Value, class Compare >
  bool RNLIter< Key, Value, Compare >::operator!=(const this_t & rhs) const noexcept
  {
    return current_ != rhs.current_;
  }

  template < class Key, class Value, class Compare >
  std::pair< Key, Value > & RNLIter< Key, Value, Compare >::operator*()
  {
    return current_->data;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > & RNLIter< Key, Value, Compare >::operator*() const
  {
    return current_->data;
  }

  template < class Key, class Value, class Compare >
  std::pair< Key, Value > * RNLIter< Key, Value, Compare >::operator->()
  {
    return std::addressof(current_->data);
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > * RNLIter< Key, Value, Compare >::operator->() const
  {
    return std::addressof(current_->data);
  }
}

#endif
