#ifndef CONSTRNLITER_HPP
#define CONSTRNLITER_HPP

#include <stack.hpp>
#include "constLNRIter.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value, class Compare >
  class ConstRNLIter: std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
  {
    using this_t = ConstRNLIter< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;

   public:
    ConstRNLIter() = default;

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const this_t & rhs) const noexcept;
    bool operator!=(const this_t & rhs) const noexcept;

    const std::pair< Key, Value > & operator*() const;
    const std::pair< Key, Value > * operator->() const;

   private:
    ConstLNRIter< Key, Value, Compare > it_;
    friend class BSTree< Key, Value, Compare >;

    ConstRNLIter(const node_t * node, Stack< const node_t * > && s);
  };

  template < class Key, class Value, class Compare >
  ConstRNLIter< Key, Value, Compare >::ConstRNLIter(const node_t * node, Stack< const node_t * > && s):
   it_(node, std::move(s))
  {}

  template < class Key, class Value, class Compare >
  ConstRNLIter< Key, Value, Compare > & ConstRNLIter< Key, Value, Compare >::operator++()
  {
    --it_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  ConstRNLIter< Key, Value, Compare > ConstRNLIter< Key, Value, Compare >::operator++(int)
  {
    auto current = *this;
    ++(*this);
    return current;
  }

  template < class Key, class Value, class Compare >
  ConstRNLIter< Key, Value, Compare > & ConstRNLIter< Key, Value, Compare >::operator--()
  {
    ++it_;
    return *this;
  }

  template < class Key, class Value, class Compare >
  ConstRNLIter< Key, Value, Compare > ConstRNLIter< Key, Value, Compare >::operator--(int)
  {
    auto current = *this;
    --(*this);
    return current;
  }

  template < class Key, class Value, class Compare >
  bool ConstRNLIter< Key, Value, Compare >::operator==(const this_t & rhs) const noexcept
  {
    return it_ == rhs.it_;
  }

  template < class Key, class Value, class Compare >
  bool ConstRNLIter< Key, Value, Compare >::operator!=(const this_t & rhs) const noexcept
  {
    return !(*this == rhs);
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > & ConstRNLIter< Key, Value, Compare >::operator*() const
  {
    return *it_;
  }

  template < class Key, class Value, class Compare >
  const std::pair< Key, Value > * ConstRNLIter< Key, Value, Compare >::operator->() const
  {
    return it_.operator->();
  }
}

#endif
