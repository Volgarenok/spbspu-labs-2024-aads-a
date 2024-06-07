#ifndef CONST_RNL_ITERATOR
#define CONST_RNL_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "const_lnr_iterator.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template< class Key, class T >
  class ConstRnlIterator: public std::iterator< std::bidirectional_iterator_tag, const std::pair< Key, T > >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;
  public:
    ConstRnlIterator() = default;
    ConstRnlIterator(const ConstRnlIterator< Key, T > &) = default;
    ~ConstRnlIterator() = default;
    ConstRnlIterator< Key, T > & operator=(const ConstRnlIterator< Key, T > &) = default;
    ConstRnlIterator< Key, T > & operator++();
    ConstRnlIterator< Key, T > operator++(int);
    ConstRnlIterator< Key, T > & operator--();
    ConstRnlIterator< Key, T > operator--(int);
    const std::pair< Key, T > & operator*() const;
    const std::pair< Key, T > * operator->() const;
    bool operator==(const ConstRnlIterator< Key, T > & rhs) const;
    bool operator!=(const ConstRnlIterator< Key, T > & rhs) const;
  private:
    ConstLnrIterator< Key, T > iter_;
    explicit ConstRnlIterator(const detail::TreeNode< Key, T > * node_ptr);
    explicit ConstRnlIterator(ConstLnrIterator< Key, T > iter);
  };

  template< class Key, class T >
  ConstRnlIterator< Key, T >::ConstRnlIterator(const detail::TreeNode< Key, T > * node_ptr):
    iter_(ConstLnrIterator< Key, T >(node_ptr))
  {}

  template< class Key, class T >
  ConstRnlIterator< Key, T >::ConstRnlIterator(ConstLnrIterator< Key, T > iter):
    iter_(iter)
  {}

  template< class Key, class T >
  ConstRnlIterator< Key, T > & ConstRnlIterator< Key, T >::operator++()
  {
    --iter_;
    return *this;
  }

  template< class Key, class T >
  ConstRnlIterator< Key, T > ConstRnlIterator< Key, T >::operator++(int)
  {
    return ConstRnlIterator< Key, T >(iter_--);
  }

  template< class Key, class T >
  ConstRnlIterator< Key, T > & ConstRnlIterator< Key, T >::operator--()
  {
    ++iter_;
    return *this;
  }

  template< class Key, class T >
  ConstRnlIterator< Key, T > ConstRnlIterator< Key, T >::operator--(int)
  {
    return ConstRnlIterator< Key, T >(iter_--);
  }

  template< class Key, class T >
  const std::pair< Key, T > & ConstRnlIterator< Key, T>::operator*() const
  {
    return iter_.operator*();
  }

  template< class Key, class T >
  const std::pair< Key, T > * ConstRnlIterator< Key, T >::operator->() const
  {
    return iter_.operator->();
  }

  template< class Key, class T >
  bool ConstRnlIterator< Key, T >::operator==(const ConstRnlIterator< Key, T > & rhs) const
  {
    return (iter_ == rhs.iter_);
  }

  template< class Key, class T >
  bool ConstRnlIterator< Key, T >::operator!=(const ConstRnlIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
