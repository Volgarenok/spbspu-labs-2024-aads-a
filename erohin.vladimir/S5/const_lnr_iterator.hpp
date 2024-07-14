#ifndef CONST_LNR_ITERATOR
#define CONST_LNR_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "stack.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template < class Key, class T >
  class ConstRnlIterator;

  template< class Key, class T >
  class ConstLnrIterator: public std::iterator< std::bidirectional_iterator_tag, const std::pair< Key, T > >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;

    template < class T1, class T2 >
    friend class ConstRnlIterator;

  public:
    ConstLnrIterator();
    ConstLnrIterator(const ConstLnrIterator< Key, T > &) = default;
    ~ConstLnrIterator() = default;
    ConstLnrIterator< Key, T > & operator=(const ConstLnrIterator< Key, T > &) = default;
    ConstLnrIterator< Key, T > & operator++();
    ConstLnrIterator< Key, T > operator++(int);
    ConstLnrIterator< Key, T > & operator--();
    ConstLnrIterator< Key, T > operator--(int);
    const std::pair< Key, T > & operator*() const;
    const std::pair< Key, T > * operator->() const;
    bool operator==(const ConstLnrIterator< Key, T > & rhs) const;
    bool operator!=(const ConstLnrIterator< Key, T > & rhs) const;
  private:
    const detail::TreeNode< Key, T > * node_;
    Stack< const detail::TreeNode< Key, T > * > stack_;
    explicit ConstLnrIterator(const detail::TreeNode< Key, T > * node_ptr);
  };

  template< class Key, class T >
  ConstLnrIterator< Key, T >::ConstLnrIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  ConstLnrIterator< Key, T >::ConstLnrIterator(const detail::TreeNode< Key, T > * node_ptr):
    node_(node_ptr)
  {}

  template< class Key, class T >
  ConstLnrIterator< Key, T > & ConstLnrIterator< Key, T >::operator++()
  {
    if (node_->right)
    {
      stack_.push(node_);
      node_ = node_->right;
      while (node_->left)
      {
        stack_.push(node_);
        node_ = node_->left;
      }
    }
    else
    {
      if (stack_.empty())
      {
        node_ = nullptr;
        return *this;
      }
      while (stack_.top()->right == node_)
      {
        node_ = stack_.top();
        stack_.pop();
        if (stack_.empty())
        {
          node_ = nullptr;
          return *this;
        }
      }
      while (!stack_.empty() && stack_.top()->left == node_)
      {
        node_ = stack_.top();
        stack_.pop();
      }
    }
    return *this;
  }

  template< class Key, class T >
  ConstLnrIterator< Key, T > ConstLnrIterator< Key, T >::operator++(int)
  {
    ConstLnrIterator< Key, T > temp = *this;
    operator++();
    return temp;
  }

  template< class Key, class T >
  ConstLnrIterator< Key, T > & ConstLnrIterator< Key, T >::operator--()
  {
    if (node_->left)
    {
      stack_.push(node_);
      node_ = node_->left;
      while (node_->right)
      {
        stack_.push(node_);
        node_ = node_->right;
      }
    }
    else
    {
      if (stack_.empty())
      {
        node_ = nullptr;
        return *this;
      }
      while (stack_.top()->left == node_)
      {
        node_ = stack_.top();
        stack_.pop();
        if (stack_.empty())
        {
          node_ = nullptr;
          return *this;
        }
      }
      while (!stack_.empty() && stack_.top()->right == node_)
      {
        node_ = stack_.top();
        stack_.pop();
      }
    }
    return *this;
  }

  template< class Key, class T >
  ConstLnrIterator< Key, T > ConstLnrIterator< Key, T >::operator--(int)
  {
    ConstLnrIterator< Key, T > temp = *this;
    operator--();
    return temp;
  }

  template< class Key, class T >
  const std::pair< Key, T > & ConstLnrIterator< Key, T>::operator*() const
  {
    return node_->data;
  }

  template< class Key, class T >
  const std::pair< Key, T > * ConstLnrIterator< Key, T >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  bool ConstLnrIterator< Key, T >::operator==(const ConstLnrIterator< Key, T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T >
  bool ConstLnrIterator< Key, T >::operator!=(const ConstLnrIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
