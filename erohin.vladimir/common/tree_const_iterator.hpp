#ifndef TREE_CONST_ITERATOR
#define TREE_CONST_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "../S5/const_rnl_iterator.hpp"
#include "../S5/const_breadth_iterator.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template < class Key, class T >
  class ConstLnrIterator;

  template < class Key, class T >
  class ConstRnlIterator;

  template < class Key, class T >
  class ConstBreadthIterator;

  template< class Key, class T >
  class TreeConstIterator: public std::iterator< std::bidirectional_iterator_tag, const std::pair< Key, T > >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;

    template < class T1, class T2 >
    friend class ConstLnrIterator;

    template < class T1, class T2 >
    friend class ConstRnlIterator;

    template < class T1, class T2 >
    friend class ConstBreadthIterator;

  public:
    TreeConstIterator();
    TreeConstIterator(const TreeConstIterator< Key, T > &) = default;
    TreeConstIterator(const ConstLnrIterator< Key, T > & iter);
    TreeConstIterator(const ConstRnlIterator< Key, T > & iter);
    TreeConstIterator(const ConstBreadthIterator< Key, T > & iter);
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
    const detail::TreeNode< Key, T > * node_;
    explicit TreeConstIterator(const detail::TreeNode< Key, T > * node_ptr);
  };

  template< class Key, class T >
  TreeConstIterator< Key, T >::TreeConstIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  TreeConstIterator< Key, T >::TreeConstIterator(const ConstLnrIterator< Key, T > & iter):
    node_(iter.node_)
  {}

  template< class Key, class T >
  TreeConstIterator< Key, T >::TreeConstIterator(const ConstRnlIterator< Key, T > & iter):
    node_(iter.node_)
  {}

  template< class Key, class T >
  TreeConstIterator< Key, T >::TreeConstIterator(const ConstBreadthIterator< Key, T > & iter):
    node_(iter.node_)
  {}

  template< class Key, class T >
  TreeConstIterator< Key, T >::TreeConstIterator(const detail::TreeNode< Key, T > * node_ptr):
    node_(node_ptr)
  {}

  template< class Key, class T >
  TreeConstIterator< Key, T > & TreeConstIterator< Key, T >::operator++()
  {
    node_ = const_cast< detail::TreeNode< Key, T > * >(node_)->next();
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
    node_ = const_cast< detail::TreeNode< Key, T > * >(node_)->prev();
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
