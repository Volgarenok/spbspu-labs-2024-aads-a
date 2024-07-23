#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include <stdexcept>
#include "treeNode.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class Tree
  {
    using bSTree = Tree< Key, Value, Compare >;

   public:
    Tree();

    //begin();
    //end();
    //at();
    //operator[]();

    size_t size() const noexcept;
    void clear() noexcept;
    void swap(bSTree & other) noexcept;
    //find(const Key & key) const;

   private:
    detail::TreeNode< Key, Value > * root_;
    Compare cmp_;
    size_t size_;
  };

  template < class Key, class Value, class Compare >
  Tree< Key, Value, Compare >::Tree():
   root_(nullptr),
   cmp_(),
   size_(0)
  {}

  template < class Key, class Value, class Compare >
  size_t Tree< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template < class Key, class Value, class Compare >
  void Tree< Key, Value, Compare >::clear() noexcept
  {
  }

  template < class Key, class Value, class Compare >
  void Tree< Key, Value, Compare >::swap(bSTree & other) noexcept
  {
    std::swap(root_, other.root_);
    std::swap(cmp_, other.cmp_);
    std::swap(size_, other.size_);
  }
}

#endif
