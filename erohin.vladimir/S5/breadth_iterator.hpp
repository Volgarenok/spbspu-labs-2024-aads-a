#ifndef BREADTH_ITERATOR
#define BREADTH_ITERATOR

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
  class BreadthIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;
  public:
    BreadthIterator();
    BreadthIterator(const BreadthIterator< Key, T > &) = default;
    ~BreadthIterator() = default;
    BreadthIterator< Key, T > & operator=(const BreadthIterator< Key, T > &) = default;
    BreadthIterator< Key, T > & operator++();
    BreadthIterator< Key, T > operator++(int);
    BreadthIterator< Key, T > & operator--();
    BreadthIterator< Key, T > operator--(int);
    std::pair< Key, T > & operator*();
    const std::pair< Key, T > & operator*() const;
    std::pair< Key, T > * operator->();
    const std::pair< Key, T > * operator->() const;
    bool operator==(const BreadthIterator< Key, T > & rhs) const;
    bool operator!=(const BreadthIterator< Key, T > & rhs) const;
  private:
    detail::TreeNode< Key, T > * node_;
    Queue< detail::TreeNode< Key, T > * > queue_;
    Stack< detail::TreeNode< Key, T > * > stack_;
    explicit BreadthIterator(detail::TreeNode< Key, T > * node_ptr);
  };

  template< class Key, class T >
  BreadthIterator< Key, T >::BreadthIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  BreadthIterator< Key, T >::BreadthIterator(detail::TreeNode< Key, T > * node_ptr):
    node_(node_ptr)
  {
    queue_.push(node_ptr);
  }

  template< class Key, class T >
  BreadthIterator< Key, T > & BreadthIterator< Key, T >::operator++()
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
  BreadthIterator< Key, T > BreadthIterator< Key, T >::operator++(int)
  {
    BreadthIterator< Key, T > temp = *this;
    operator++();
    return temp;
  }

  template< class Key, class T >
  BreadthIterator< Key, T > & BreadthIterator< Key, T >::operator--()
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
  BreadthIterator< Key, T > BreadthIterator< Key, T >::operator--(int)
  {
    BreadthIterator< Key, T > temp = *this;
    operator--();
    return temp;
  }

  template< class Key, class T >
  std::pair< Key, T > & BreadthIterator< Key, T>::operator*()
  {
    return node_->data;
  }

  template< class Key, class T >
  const std::pair< Key, T > & BreadthIterator< Key, T>::operator*() const
  {
    return node_->data;
  }

  template< class Key, class T >
  std::pair< Key, T > * BreadthIterator< Key, T >::operator->()
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  const std::pair< Key, T > * BreadthIterator< Key, T >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  bool BreadthIterator< Key, T >::operator==(const BreadthIterator< Key, T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T >
  bool BreadthIterator< Key, T >::operator!=(const BreadthIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
