#ifndef CONST_BREADTH_ITERATOR
#define CONST_BREADTH_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "queue.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template< class Key, class T >
  class ConstBreadthIterator: public std::iterator< std::forward_iterator_tag, T >
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
    const std::pair< Key, T > & operator*() const;
    const std::pair< Key, T > * operator->() const;
    bool operator==(const ConstBreadthIterator< Key, T > & rhs) const;
    bool operator!=(const ConstBreadthIterator< Key, T > & rhs) const;
  private:
    const detail::Node< Key, T > * node_;
    Queue< const detail::Node< Key, T > * > queue_;
    Queue< const detail::Node< Key, T > * > layer_queue_;
    explicit ConstBreadthIterator(const detail::Node< Key, T > * node_ptr);
  };

  template< class Key, class T >
  ConstBreadthIterator< Key, T >::ConstBreadthIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  ConstBreadthIterator< Key, T >::ConstBreadthIterator(const detail::Node< Key, T > * node_ptr):
    node_(node_ptr)
  {
    layer_queue_.push(node_ptr);
  }

  template< class Key, class T >
  ConstBreadthIterator< Key, T > & ConstBreadthIterator< Key, T >::operator++()
  {
    if (queue_.empty())
    {
      while (!layer_queue_.empty())
      {
        if (layer_queue_.front()->left)
        {
          queue_.push(layer_queue_.front()->left);
        }
        if (layer_queue_.front()->right)
        {
          queue_.push(layer_queue_.front()->right);
        }
        layer_queue_.pop();
      }
      if (queue_.empty())
      {
        node_ = nullptr;
        return *this;
      }
      else
      {
        layer_queue_ = queue_;
      }
    }
    node_ = queue_.front();
    queue_.pop();
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
