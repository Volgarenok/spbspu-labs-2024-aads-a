#ifndef TREE_CONST_ITERATOR
#define TREE_CONST_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "tree_iterator.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template< class Key, class T >
  class TreeConstIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;
  public:
    TreeConstIterator();
    TreeConstIterator(const TreeConstIterator< Key, T > &) = default;
    ~TreeConstIterator() = default;
    TreeConstIterator< Key, T > & operator=(const TreeConstIterator< Key, T > &) = default;
    TreeConstIterator< Key, T > & operator++();
    TreeConstIterator< Key, T > operator++(int);
    TreeConstIterator< Key, T > & operator--();
    TreeConstIterator< Key, T > operator--(int);
    const std::pair< Key, T > & operator*() const;
    const std::pair< Key, T > * operator->() const;
    bool operator==(const TreeConstIterator< Key, T > & rhs) const;
    bool operator!=(const TreeConstIterator< Key, T > & rhs) const;
  private:
    const detail::Node< Key, T > * node_;
    explicit TreeConstIterator(const detail::Node< Key, T > * node_ptr);
  };

  template< class Key, class T >
  TreeConstIterator< Key, T >::TreeConstIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  TreeConstIterator< Key, T >::TreeConstIterator(const detail::Node< Key, T > * node_ptr):
    node_(node_ptr)
  {}

  template< class Key, class T >
  TreeConstIterator< Key, T > & TreeConstIterator< Key, T >::operator++()
  {
    node_ = const_cast< detail::Node< Key, T > * >(node_)->next();
    return *this;
  }

  template< class Key, class T >
  TreeConstIterator< Key, T > TreeConstIterator< Key, T >::operator++(int)
  {
    TreeConstIterator< Key, T > temp = *this;
    operator++();
    return temp;
  }

  template< class Key, class T >
  TreeConstIterator< Key, T > & TreeConstIterator< Key, T >::operator--()
  {
    node_ = const_cast< detail::Node< Key, T > * >(node_)->prev();
    return *this;
  }

  template< class Key, class T >
  TreeConstIterator< Key, T > TreeConstIterator< Key, T >::operator--(int)
  {
    TreeConstIterator< Key, T > temp = *this;
    operator--();
    return temp;
  }

  template< class Key, class T >
  const std::pair< Key, T > & TreeConstIterator< Key, T>::operator*() const
  {
    return node_->data;
  }

  template< class Key, class T >
  const std::pair< Key, T > * TreeConstIterator< Key, T >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  bool TreeConstIterator< Key, T >::operator==(const TreeConstIterator< Key, T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T >
  bool TreeConstIterator< Key, T >::operator!=(const TreeConstIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
