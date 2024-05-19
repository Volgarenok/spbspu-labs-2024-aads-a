#ifndef CONSTTREEITERATOR_HPP
#define CONSTTREEITERATOR_HPP

#include <functional>
#include <iterator>
#include <utility>

namespace marishin
{
  template < class Key, class Value, class Compare >
  class BinarySearchTree;

  template < class Key, class Value, class Compare = std::less< Key > >
  struct ConstIteratorTree:
  {
    friend class BinarySearchTree< Key, Value, Compare >;
    using this_t = ConstIteratorTree< Key, Value, Compare >;
    using TreeNode = detail::TreeNode< Key, Value >;

    ConstIteratorTree() = default;
    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;
    const std::pair< Key, Value >& operator*() const;
    const std::pair< Key, Value >* operator->() const;

  private:
    detail::TreeNode< Key, Value >* node_;
    ConstIteratorTree(detail::TreeNode< Key, Value >* node);
  };
}
