#ifndef CONST_TREE_ITERATOR_HPP
#define CONST_TREE_ITERATOR_HPP

#include "tree_node.hpp"

namespace nikitov
{
  template< class Key, class T, class Compare >
  class Tree;

  template< class Key, class T, class Compare = std::less< Key > >
  class ConstTreeIterator
  {
    friend class Tree< Key, T, Compare >;
  public:
    explicit ConstTreeIterator(detail::TreeNode< Key, T, Compare >* node);
    ~ConstTreeIterator() = default;

  private:
    detail::TreeNode< Key, T, Compare >* node_;
  };

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare >::ConstTreeIterator(detail::TreeNode< Key, T, Compare >* node):
    node_(node)
  {}
}
#endif
