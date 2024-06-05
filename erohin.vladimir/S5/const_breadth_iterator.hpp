#ifndef CONST_BREADTH_ITERATOR
#define CONST_BREADTH_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "queue.hpp"
#include "stack.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template< class Key, class T >
  class ConstBreadthIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;
  public:
    ConstBreadthIterator();
    ConstBreadthIterator(const ConstBreadthIterator< Key, T > &) = default;
    ~ConstBreadthIterator() = default;
    ConstBreadthIterator< Key, T > & operator=(const ConstBreadthIterator< Key, T > &) = default;
    ConstBreadthIterator< Key, T > & operator++();
    ConstBreadthIterator< Key, T > operator++(int);
    ConstBreadthIterator< Key, T > & operator--();
    ConstBreadthIterator< Key, T > operator--(int);
    const std::pair< Key, T > & operator*() const;
    const std::pair< Key, T > * operator->() const;
    bool operator==(const ConstBreadthIterator< Key, T > & rhs) const;
    bool operator!=(const ConstBreadthIterator< Key, T > & rhs) const;
  private:
    const detail::TreeNode< Key, T > * node_;
    Queue< const detail::TreeNode< Key, T > * > queue_;
    Stack< const detail::TreeNode< Key, T > * > stack_;
    explicit ConstBreadthIterator(const detail::TreeNode< Key, T > * node_ptr);
  };

  template< class Key, class T >
  ConstBreadthIterator< Key, T >::ConstBreadthIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  ConstBreadthIterator< Key, T >::ConstBreadthIterator(const detail::TreeNode< Key, T > * node_ptr):
    node_(node_ptr)
  {
    queue_.push(node_ptr);
  }

  template< class Key, class T >
  ConstBreadthIterator< Key, T > & ConstBreadthIterator< Key, T >::operator++()
  {
    if (queue_.empty())
    {
      node_ = nullptr;
    }
    else
    {
      node_ = queue_.front();
      if (node_->left)
      {
        queue_.push(node_->left);
      }
      if (node_->right)
      {
        queue_.push(node_->right);
      }
      stack_.push(node_);
      queue_.pop();
      if (queue_.empty())
      {
        node_ = nullptr;
      }
      else
      {
        node_ = queue_.front();
      }
    }
    return *this;
  }

  template< class Key, class T >
  ConstBreadthIterator< Key, T > ConstBreadthIterator< Key, T >::operator++(int)
  {
    ConstBreadthIterator< Key, T > temp = *this;
    operator++();
    return temp;
  }

  template< class Key, class T >
  ConstBreadthIterator< Key, T > & ConstBreadthIterator< Key, T >::operator--()
  {
    if (stack_.empty())
    {
      node_ = nullptr;
    }
    else
    {
      node_ = stack_.top();
      stack_.pop();
      queue_.push(node_);
    }
    return *this;
  }

  template< class Key, class T >
  ConstBreadthIterator< Key, T > ConstBreadthIterator< Key, T >::operator--(int)
  {
    ConstBreadthIterator< Key, T > temp = *this;
    operator--();
    return temp;
  }

  template< class Key, class T >
  const std::pair< Key, T > & ConstBreadthIterator< Key, T>::operator*() const
  {
    return node_->data;
  }

  template< class Key, class T >
  const std::pair< Key, T > * ConstBreadthIterator< Key, T >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  bool ConstBreadthIterator< Key, T >::operator==(const ConstBreadthIterator< Key, T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T >
  bool ConstBreadthIterator< Key, T >::operator!=(const ConstBreadthIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
