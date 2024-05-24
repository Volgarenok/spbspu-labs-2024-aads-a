#ifndef RNL_ITERATOR
#define RNL_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "lnr_iterator.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template< class Key, class T >
  class RnlIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, T > >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;
  public:
    RnlIterator() = default;
    RnlIterator(const RnlIterator< Key, T > &) = default;
    ~RnlIterator() = default;
    RnlIterator< Key, T > & operator=(const RnlIterator< Key, T > &) = default;
    RnlIterator< Key, T > & operator++();
    RnlIterator< Key, T > operator++(int);
    RnlIterator< Key, T > & operator--();
    RnlIterator< Key, T > operator--(int);
    std::pair< Key, T > & operator*();
    const std::pair< Key, T > & operator*() const;
    std::pair< Key, T > * operator->();
    const std::pair< Key, T > * operator->() const;
    bool operator==(const RnlIterator< Key, T > & rhs) const;
    bool operator!=(const RnlIterator< Key, T > & rhs) const;
  private:
    LnrIterator< Key, T > iter_;
    explicit RnlIterator(detail::TreeNode< Key, T > * node_ptr);
    explicit RnlIterator(LnrIterator< Key, T > iter);
  };

  template< class Key, class T >
  RnlIterator< Key, T >::RnlIterator(detail::TreeNode< Key, T > * node_ptr):
    iter_(LnrIterator< Key, T >(node_ptr))
  {}

  template< class Key, class T >
  RnlIterator< Key, T >::RnlIterator(LnrIterator< Key, T > iter):
    iter_(iter)
  {}

  template< class Key, class T >
  RnlIterator< Key, T > & RnlIterator< Key, T >::operator++()
  {
    return (--iter_);
  }

  template< class Key, class T >
  RnlIterator< Key, T > RnlIterator< Key, T >::operator++(int)
  {
    return (iter_--);
  }

  template< class Key, class T >
  RnlIterator< Key, T > & RnlIterator< Key, T >::operator--()
  {
    return (++iter_);
  }

  template< class Key, class T >
  RnlIterator< Key, T > RnlIterator< Key, T >::operator--(int)
  {
    return (iter_--);
  }

  template< class Key, class T >
  std::pair< Key, T > & RnlIterator< Key, T>::operator*()
  {
    return iter_.operator*();
  }

  template< class Key, class T >
  const std::pair< Key, T > & RnlIterator< Key, T>::operator*() const
  {
    return iter_.operator*();
  }

  template< class Key, class T >
  std::pair< Key, T > * RnlIterator< Key, T >::operator->()
  {
    return iter_.operator->();
  }

  template< class Key, class T >
  const std::pair< Key, T > * RnlIterator< Key, T >::operator->() const
  {
    return iter_.operator->();
  }

  template< class Key, class T >
  bool RnlIterator< Key, T >::operator==(const RnlIterator< Key, T > & rhs) const
  {
    return (iter_ == rhs.iter_);
  }

  template< class Key, class T >
  bool RnlIterator< Key, T >::operator!=(const RnlIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
