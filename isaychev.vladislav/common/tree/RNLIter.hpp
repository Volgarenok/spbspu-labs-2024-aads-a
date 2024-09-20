#ifndef RNLITER_HPP
#define RNLITER_HPP

#include <stack.hpp>
#include "LNRIter.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class RNLIter: std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
  {
    using this_t = RNLIter< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;

   public:
    RNLIter() = default;

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const this_t & rhs) const noexcept;
    bool operator!=(const this_t & rhs) const noexcept;

    std::pair< Key, Value > & operator*();
    const std::pair< Key, Value > & operator*() const;
    std::pair< Key, Value > * operator->();
    const std::pair< Key, Value > * operator->() const;

   private:
    LNRIter< Key, Value, Compare > it_;

    friend class BSTree< Key, Value, Compare >;
    RNLIter(node_t * node, Stack< node_t * > && s);
  };

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare >:: RNLIter(node_t * node, Stack< node_t * > && s):
   it_(node, std::forward(s))
  {}

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare > & RNLIter< Key, Value, Compare >::operator++()
  {
    --it_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare > RNLIter< Key, Value, Compare >::operator++(int)
  {
    auto current = *this;
    ++(*this);
    return current;
  }

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare > & RNLIter< Key, Value, Compare >::operator--()
  {
    ++it_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare > RNLIter< Key, Value, Compare >::operator--(int)
  {
    auto current = *this;
    --(*this);
    return current;
  }

  template < class Key, class Value, class Compare >
  bool RNLIter< Key, Value, Compare >::operator==(const this_t & rhs) const noexcept
  {
    return it_ == rhs.it_;
  }

  template < class Key, class Value, class Compare >
  bool RNLIter< Key, Value, Compare >::operator!=(const this_t & rhs) const noexcept
  {
    return !(*this == rhs);
  }

  template < class Key, class Value, class Compare >
  std::pair< Key, Value > & RNLIter< Key, Value, Compare >::operator*()
  {
    return *it_;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > & RNLIter< Key, Value, Compare >::operator*() const
  {
    return *it_;
  }

  template < class Key, class Value, class Compare >
  std::pair< Key, Value > * RNLIter< Key, Value, Compare >::operator->()
  {
    return it_.operator->();
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > * RNLIter< Key, Value, Compare >::operator->() const
  {
    return it_.operator->();
  }
}

#endif
