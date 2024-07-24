#ifndef CONSTITER_HPP
#define CONSTITER_HPP

#include <iterator>
#include "treeNode.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class ConstTreeIter: public std::iterator< bidirectional_iterator_tag, Key, Value, Compare >
  {
    using this_t = ConstTreeIter< Key, Value, Compare >;

   public:
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const ConstTreeIter & rhs);
    bool operator!=(const ConstTreeIter & rhs);

    const T & operator*() const;
    const T * operator->() const;

   private:
    detail::TreeNode< Key, Value, Compare > * parent;
    friend class BSTree< Key, Value, Compare >;
  };

  template < class Key, class Value, class Compare >
  this_t & ConstTreeIter< Key, Value, Compare >::operator++()
  {}

  template < class Key, class Value, class Compare >
  this_t ConstTreeIter< Key, Value, Compare >::operator++(int)
  {}

  template < class Key, class Value, class Compare >
  this_t & ConstTreeIter< Key, Value, Compare >::operator--()
  {}

  template < class Key, class Value, class Compare >
  this_t ConstTreeIter< Key, Value, Compare >::operator--(int)
  {}

  template < class Key, class Value, class Compare >
  bool ConstTreeIter< Key, Value, Compare >::operator==(const ConstTreeIter & rhs)
  {}

  template < class Key, class Value, class Compare >
  bool ConstTreeIter< Key, Value, Compare >::operator!=(const ConstTreeIter & rhs)
  {}

  template < class Key, class Value, class Compare >
  const T & ConstTreeIter< Key, Value, Compare >::operator*() const
  {}

  template < class Key, class Value, class Compare >
  const T * ConstTreeIter< Key, Value, Compare >::operator->() const
  {}
}

#endif
