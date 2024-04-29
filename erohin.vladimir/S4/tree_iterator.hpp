#ifndef TREE_ITERATOR
#define TREE_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "traversal_strategy.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template< class Key, class T, class S = detail::InfixTraversal< Key, T > >
  class TreeIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;

  public:
    TreeIterator();
    TreeIterator(const TreeIterator< Key, T, S > &) = default;
    ~TreeIterator() = default;
    TreeIterator< Key, T, S > & operator=(const TreeIterator< Key, T, S > &) = default;
    TreeIterator< Key, T, S > & operator++();
    TreeIterator< Key, T, S > operator++(int);
    TreeIterator< Key, T, S > & operator--();
    TreeIterator< Key, T, S > operator--(int);
    std::pair< Key, T > & operator*();
    const std::pair< Key, T > & operator*() const;
    std::pair< Key, T > * operator->();
    const std::pair< Key, T > * operator->() const;
    bool operator==(const TreeIterator< Key, T, S > & rhs) const;
    bool operator!=(const TreeIterator< Key, T, S > & rhs) const;
  private:
    detail::Node< Key, T > * node_;
    S strategy_;
    explicit TreeIterator(detail::Node< Key, T > * node_ptr);
  };

  template< class Key, class T, class S >
  TreeIterator< Key, T, S >::TreeIterator():
    node_(nullptr)
  {}

  template< class Key, class T, class S >
  TreeIterator< Key, T, S >::TreeIterator(detail::Node< Key, T > * node_ptr):
    node_(node_ptr)
  {}

  template< class Key, class T, class S >
  TreeIterator< Key, T, S > & TreeIterator< Key, T, S >::operator++()
  {
    node_ = strategy_(node_);
    return *this;
  }

  template< class Key, class T, class S >
  TreeIterator< Key, T, S > TreeIterator< Key, T, S >::operator++(int)
  {
    TreeIterator< Key, T, S > temp = *this;
    node_ = strategy_.next(node_);
    return temp;
  }

  template< class Key, class T, class S >
  TreeIterator< Key, T, S > & TreeIterator< Key, T, S >::operator--()
  {
    node_ = strategy_.prev(node_);
    return *this;
  }

  template< class Key, class T, class S >
  TreeIterator< Key, T, S > TreeIterator< Key, T, S >::operator--(int)
  {
    TreeIterator< Key, T, S > temp = *this;
    node_ = strategy_.prev(node_);
    return temp;
  }

  template< class Key, class T, class S >
  std::pair< Key, T > & TreeIterator< Key, T, S>::operator*()
  {
    return node_->data_;
  }

  template< class Key, class T, class S >
  const std::pair< Key, T > & TreeIterator< Key, T, S>::operator*() const
  {
    return node_->data_;
  }

  template< class Key, class T, class S >
  std::pair< Key, T > * TreeIterator< Key, T, S >::operator->()
  {
    return std::addressof(node_->data_);
  }

  template< class Key, class T, class S >
  const std::pair< Key, T > * TreeIterator< Key, T, S >::operator->() const
  {
    return std::addressof(node_->data_);
  }

  template< class Key, class T, class S >
  bool TreeIterator< Key, T, S >::operator==(const TreeIterator< Key, T, S > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T, class S >
  bool TreeIterator< Key, T, S >::operator!=(const TreeIterator< Key, T, S > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
