#ifndef REVTREEITER_HPP
#define REVTREEITER_HPP

#include <iterator>
#include "treeNode.hpp"
#include "treeIter.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class RevTreeIter: public std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
  {
    using this_t = RevTreeIter< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;

   public:
    RevTreeIter();

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const this_t & rhs);
    bool operator!=(const this_t & rhs);

    std::pair< Key, Value > & operator*();
    const std::pair< Key, Value > & operator*() const;
    std::pair< Key, Value > * operator->();
    const std::pair< Key, Value > * operator->() const;

   private:
    TreeIter< Key, Value, Compare > current_;
    friend class BSTree< Key, Value, Compare >;

    explicit RevTreeIter(node_t * node);
  };

  template < class Key, class Value, class Compare >
  RevTreeIter< Key, Value, Compare >::RevTreeIter():
   current_(nullptr)
  {}

  template < class Key, class Value, class Compare >
  RevTreeIter< Key, Value, Compare >::RevTreeIter(node_t * node):
   current_(node)
  {}

  template < class Key, class Value, class Compare >
  RevTreeIter< Key, Value, Compare > & RevTreeIter< Key, Value, Compare >::operator++()
  {
    --current_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  RevTreeIter< Key, Value, Compare > RevTreeIter< Key, Value, Compare >::operator++(int)
  {
    auto iter = *this;
    ++(*this);
    return iter;
  }

  template < class Key, class Value, class Compare >
  RevTreeIter< Key, Value, Compare > & RevTreeIter< Key, Value, Compare >::operator--()
  {
    ++current_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  RevTreeIter< Key, Value, Compare > RevTreeIter< Key, Value, Compare >::operator--(int)
  {
    auto iter = *this;
    --(*this);
    return iter;
  }

  template < class Key, class Value, class Compare >
  bool RevTreeIter< Key, Value, Compare >::operator==(const this_t & rhs)
  {
    return current_ == rhs.current_;
  }

  template < class Key, class Value, class Compare >
  bool RevTreeIter< Key, Value, Compare >::operator!=(const this_t & rhs)
  {
    return !(*this == rhs);
  }

  template < class Key, class Value, class Compare >
  std::pair< Key, Value > & RevTreeIter< Key, Value, Compare >::operator*()
  {
    return *current_;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > & RevTreeIter< Key, Value, Compare >::operator*() const
  {
    return *current_;
  }

  template < class Key, class Value, class Compare >
  std::pair< Key, Value > * RevTreeIter< Key, Value, Compare >::operator->()
  {
    return current_.operator->();
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > * RevTreeIter< Key, Value, Compare >::operator->() const
  {
    return current_.operator->();
  }
}

#endif
