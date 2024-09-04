#ifndef CONSTREVTREEITER_HPP
#define CONSTREVTREEITER_HPP

#include <iterator>
#include "treeNode.hpp"
#include "constTreeIter.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class ConstRevTreeIter: public std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
  {
    using this_t = ConstRevTreeIter< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;

   public:
    ConstRevTreeIter();

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const this_t & rhs);
    bool operator!=(const this_t & rhs);

    const std::pair< Key, Value > & operator*() const;
    const std::pair< Key, Value > * operator->() const;

   private:
    ConstTreeIter< Key, Value, Compare > current_;
    friend class BSTree< Key, Value, Compare >;

    explicit ConstRevTreeIter(node_t * node);
  };

  template < class Key, class Value, class Compare >
  ConstRevTreeIter< Key, Value, Compare >::ConstRevTreeIter():
   current_(nullptr)
  {}

  template < class Key, class Value, class Compare >
  ConstRevTreeIter< Key, Value, Compare >::ConstRevTreeIter(node_t * node):
   current_(node)
  {}

  template < class Key, class Value, class Compare >
  ConstRevTreeIter< Key, Value, Compare > & ConstRevTreeIter< Key, Value, Compare >::operator++()
  {
    --current_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  ConstRevTreeIter< Key, Value, Compare > ConstRevTreeIter< Key, Value, Compare >::operator++(int)
  {
    auto iter = *this;
    ++(*this);
    return iter;
  }

  template < class Key, class Value, class Compare >
  ConstRevTreeIter< Key, Value, Compare > & ConstRevTreeIter< Key, Value, Compare >::operator--()
  {
    ++current_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  ConstRevTreeIter< Key, Value, Compare > ConstRevTreeIter< Key, Value, Compare >::operator--(int)
  {
    auto iter = *this;
    --(*this);
    return iter;
  }

  template < class Key, class Value, class Compare >
  bool ConstRevTreeIter< Key, Value, Compare >::operator==(const this_t & rhs)
  {
    return current_ == rhs.current_;
  }

  template < class Key, class Value, class Compare >
  bool ConstRevTreeIter< Key, Value, Compare >::operator!=(const this_t & rhs)
  {
    return !(*this == rhs);
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > & ConstRevTreeIter< Key, Value, Compare >::operator*() const
  {
    return *current_;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > * ConstRevTreeIter< Key, Value, Compare >::operator->() const
  {
    return current_.operator->();
  }
}

#endif
