#ifndef LNR_ITERATOR
#define LNR_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "stack.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template < class Key, class T >
  class RnlIterator;

  template< class Key, class T >
  class LnrIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, T > >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;

    template < class T1, class T2 >
    friend class RnlIterator;

  public:
    LnrIterator();
    LnrIterator(const LnrIterator< Key, T > &) = default;
    ~LnrIterator() = default;
    LnrIterator< Key, T > & operator=(const LnrIterator< Key, T > &) = default;
    LnrIterator< Key, T > & operator++();
    LnrIterator< Key, T > operator++(int);
    LnrIterator< Key, T > & operator--();
    LnrIterator< Key, T > operator--(int);
    std::pair< Key, T > & operator*();
    const std::pair< Key, T > & operator*() const;
    std::pair< Key, T > * operator->();
    const std::pair< Key, T > * operator->() const;
    bool operator==(const LnrIterator< Key, T > & rhs) const;
    bool operator!=(const LnrIterator< Key, T > & rhs) const;
  private:
    detail::TreeNode< Key, T > * node_;
    Stack< detail::TreeNode< Key, T > * > stack_;
    explicit LnrIterator(detail::TreeNode< Key, T > * node_ptr);
  };

  template< class Key, class T >
  LnrIterator< Key, T >::LnrIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  LnrIterator< Key, T >::LnrIterator(detail::TreeNode< Key, T > * node_ptr):
    node_(node_ptr)
  {}

  template< class Key, class T >
  LnrIterator< Key, T > & LnrIterator< Key, T >::operator++()
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
  LnrIterator< Key, T > LnrIterator< Key, T >::operator++(int)
  {
    LnrIterator< Key, T > temp = *this;
    operator++();
    return temp;
  }

  template< class Key, class T >
  LnrIterator< Key, T > & LnrIterator< Key, T >::operator--()
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
  LnrIterator< Key, T > LnrIterator< Key, T >::operator--(int)
  {
    LnrIterator< Key, T > temp = *this;
    operator--();
    return temp;
  }

  template< class Key, class T >
  std::pair< Key, T > & LnrIterator< Key, T>::operator*()
  {
    return node_->data;
  }

  template< class Key, class T >
  const std::pair< Key, T > & LnrIterator< Key, T>::operator*() const
  {
    return node_->data;
  }

  template< class Key, class T >
  std::pair< Key, T > * LnrIterator< Key, T >::operator->()
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  const std::pair< Key, T > * LnrIterator< Key, T >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  bool LnrIterator< Key, T >::operator==(const LnrIterator< Key, T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T >
  bool LnrIterator< Key, T >::operator!=(const LnrIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
