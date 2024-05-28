#ifndef TREE_ITERATOR
#define TREE_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "../S5/rnl_iterator.hpp"
#include "../S5/breadth_iterator.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template < class Key, class T >
  class LnrIterator;

  template < class Key, class T >
  class RnlIterator;

  template < class Key, class T >
  class BreadthIterator;

  template< class Key, class T >
  class TreeIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, T > >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;

    template < class T1, class T2, class T3 >
    friend class RedBlackTree;

    template < class T1, class T2 >
    friend class LnrIterator;

    template < class T1, class T2 >
    friend class RnlIterator;

    template < class T1, class T2 >
    friend class BreadthIterator;

  public:
    TreeIterator();
    TreeIterator(const TreeIterator< Key, T > &) = default;
    TreeIterator(const LnrIterator< Key, T > & iter);
    TreeIterator(const RnlIterator< Key, T > & iter);
    TreeIterator(const BreadthIterator< Key, T > & iter);
    ~TreeIterator() = default;
    TreeIterator< Key, T > & operator=(const TreeIterator< Key, T > &) = default;
    TreeIterator< Key, T > & operator++();
    TreeIterator< Key, T > operator++(int);
    TreeIterator< Key, T > & operator--();
    TreeIterator< Key, T > operator--(int);
    std::pair< Key, T > & operator*();
    const std::pair< Key, T > & operator*() const;
    std::pair< Key, T > * operator->();
    const std::pair< Key, T > * operator->() const;
    bool operator==(const TreeIterator< Key, T > & rhs) const;
    bool operator!=(const TreeIterator< Key, T > & rhs) const;
  private:
    detail::TreeNode< Key, T > * node_;
    explicit TreeIterator(detail::TreeNode< Key, T > * node_ptr);
  };

  template< class Key, class T >
  TreeIterator< Key, T >::TreeIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  TreeIterator< Key, T >::TreeIterator(const LnrIterator< Key, T > & iter):
    node_(iter.node_)
  {}

  template< class Key, class T >
  TreeIterator< Key, T >::TreeIterator(const RnlIterator< Key, T > & iter):
    node_(iter.node_)
  {}

  template< class Key, class T >
  TreeIterator< Key, T >::TreeIterator(const BreadthIterator< Key, T > & iter):
    node_(iter.node_)
  {}

  template< class Key, class T >
  TreeIterator< Key, T >::TreeIterator(detail::TreeNode< Key, T > * node_ptr):
    node_(node_ptr)
  {}

  template< class Key, class T >
  TreeIterator< Key, T > & TreeIterator< Key, T >::operator++()
  {
    node_ = node_->next();
    return *this;
  }

  template< class Key, class T >
  TreeIterator< Key, T > TreeIterator< Key, T >::operator++(int)
  {
    TreeIterator< Key, T > temp = *this;
    operator++();
    return temp;
  }

  template< class Key, class T >
  TreeIterator< Key, T > & TreeIterator< Key, T >::operator--()
  {
    node_ = node_->prev();
    return *this;
  }

  template< class Key, class T >
  TreeIterator< Key, T > TreeIterator< Key, T >::operator--(int)
  {
    TreeIterator< Key, T > temp = *this;
    operator--();
    return temp;
  }

  template< class Key, class T >
  std::pair< Key, T > & TreeIterator< Key, T>::operator*()
  {
    return node_->data;
  }

  template< class Key, class T >
  const std::pair< Key, T > & TreeIterator< Key, T>::operator*() const
  {
    return node_->data;
  }

  template< class Key, class T >
  std::pair< Key, T > * TreeIterator< Key, T >::operator->()
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  const std::pair< Key, T > * TreeIterator< Key, T >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  bool TreeIterator< Key, T >::operator==(const TreeIterator< Key, T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T >
  bool TreeIterator< Key, T >::operator!=(const TreeIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
