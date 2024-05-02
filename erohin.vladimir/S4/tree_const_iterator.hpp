#ifndef TREE_CONST_ITERATOR
#define TREE_CONST_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "tree_iterator.hpp"
#include "traversal_strategy.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template< class Key, class T, class S = detail::InfixTraversal< Key, T > >
  class TreeConstIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;
  public:
    TreeConstIterator();
    TreeConstIterator(const TreeConstIterator< Key, T, S > &) = default;
    ~TreeConstIterator() = default;
    TreeConstIterator< Key, T, S > & operator=(const TreeConstIterator< Key, T, S > &) = default;
    TreeConstIterator< Key, T, S > & operator++();
    TreeConstIterator< Key, T, S > operator++(int);
    TreeConstIterator< Key, T, S > & operator--();
    TreeConstIterator< Key, T, S > operator--(int);
    const std::pair< Key, T > & operator*() const;
    const std::pair< Key, T > * operator->() const;
    bool operator==(const TreeConstIterator< Key, T, S > & rhs) const;
    bool operator!=(const TreeConstIterator< Key, T, S > & rhs) const;
  private:
    const detail::Node< Key, T > * node_;
    S strategy_;
    explicit TreeConstIterator(const detail::Node< Key, T > * node_ptr);
  };

  template< class Key, class T, class S >
  TreeConstIterator< Key, T, S >::TreeConstIterator():
    node_(nullptr)
  {}

  template< class Key, class T, class S >
  TreeConstIterator< Key, T, S >::TreeConstIterator(const detail::Node< Key, T > * node_ptr):
    node_(node_ptr)
  {}

  template< class Key, class T, class S >
  TreeConstIterator< Key, T, S > & TreeConstIterator< Key, T, S >::operator++()
  {
    node_ = strategy_.next(node_);
    return *this;
  }

  template< class Key, class T, class S >
  TreeConstIterator< Key, T, S > TreeConstIterator< Key, T, S >::operator++(int)
  {
    TreeConstIterator< Key, T, S > temp = *this;
    node_ = strategy_.next(node_);
    return temp;
  }

  template< class Key, class T, class S >
  TreeConstIterator< Key, T, S > & TreeConstIterator< Key, T, S >::operator--()
  {
    node_ = strategy_.prev(node_);
    return *this;
  }

  template< class Key, class T, class S >
  TreeConstIterator< Key, T, S > TreeConstIterator< Key, T, S >::operator--(int)
  {
    TreeConstIterator< Key, T, S > temp = *this;
    node_ = strategy_.prev(node_);
    return temp;
  }

  template< class Key, class T, class S >
  const std::pair< Key, T > & TreeConstIterator< Key, T, S>::operator*() const
  {
    return node_->data_;
  }

  template< class Key, class T, class S >
  const std::pair< Key, T > * TreeConstIterator< Key, T, S >::operator->() const
  {
    return std::addressof(node_->data_);
  }

  template< class Key, class T, class S >
  bool TreeConstIterator< Key, T, S >::operator==(const TreeConstIterator< Key, T, S > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T, class S >
  bool TreeConstIterator< Key, T, S >::operator!=(const TreeConstIterator< Key, T, S > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
