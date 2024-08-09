#ifndef CONSTLNRITER_HPP
#define CONSTLNRITER_HPP

#include <stack>

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

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

    std::pair< Key, Value > & operator*();
    const std::pair< Key, Value > & operator*() const;
    std::pair< Key, Value > * operator->();
    const std::pair< Key, Value > * operator->() const;

   private:
    node_t * current_;
    std::stack< node_t * > stack_;
    friend class BSTree< Key, Value, Compare >;

    ConstLNRIter(node_t * node, std::stack< node_t * > && s);
  };

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare >::ConstLNRIter(node_t * node, std::stack< node_t * > && s):
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
      do
      {
        current_ = stack_.top();
        stack_.pop();
      }
      while (!stack_.empty() && stack_.top()->right == current_);
      if (stack_.empty())
      {
        current_ = nullptr;
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
      do
      {
        current_ = stack_.top();
        stack_.pop();
      }
      while (!stack_.empty() && stack_.top()->left == current_);
      if (stack_.empty())
      {
        current_ = nullptr;
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
    return std::addressof(current_);
  }
}

#endif
